import vk
import os
import json
import math
import sys
import pandas as pd

from IPython.qt.console.rich_ipython_widget import RichIPythonWidget
from IPython.qt.inprocess import QtInProcessKernelManager
from IPython.lib import guisupport

#import numpy as np
#from PythonQt.QtGui import *
#from PythonQt import *

def print_process_id():
    print('Process ID is:', os.getpid())


class DataMain():
    def __init__(self, fileName = None):
        if not fileName is None:
            self.setFileName(fileName)

    # Parsing members list from cpp by Pandas to 7 separated lists to use it in qml from cpp
    def parse(self, jsonString):
       final = jsonString
       data = pd.DataFrame.from_records(final)
       fn = data['first_name'].astype(str).tolist()
       ln = data['last_name'].astype(str).tolist()
       id = data['id'].astype(str).tolist()
       p100 = data['photo_100'].astype(str).tolist()
       p50 = data['photo_50'].astype(str).tolist()
       pid = data['photo_id'].astype(str).tolist()
       sex = data['sex'].astype(str).tolist()
       #print(lks)

       return fn, ln, id, p100, p50, pid, sex

    def fileName(self, group, offs, count):
        print(group, offs, count)
        session = vk.AuthSession(app_id='5494949', user_login='380671842805', user_password='warchiefmarkus')
        api = vk.API(session)
        #memCount = api.groups.getById(group_id=groupid, fields='members_count')[0]['members_count']
        return ''

    def setFileName(self, fileName):
        self.fn = fileName

    def showQtConsole(self, some):
        # Print the ID of the main process

        print_process_id()

        app = guisupport.get_app_qt4()

        # Create an in-process kernel
        # >>> print_process_id()
        # will print the same process ID as the main process
        kernel_manager = QtInProcessKernelManager()
        kernel_manager.start_kernel()
        kernel = kernel_manager.kernel
        kernel.gui = 'qt4'
        kernel.shell.push({'foo': 43, 'print_process_id': print_process_id})

        kernel_client = kernel_manager.client()
        kernel_client.start_channels()

        def stop():
            kernel_client.stop_channels()
            kernel_manager.shutdown_kernel()
            app.exit()

        control = RichIPythonWidget()
        control.kernel_manager = kernel_manager
        control.kernel_client = kernel_client
        control.exit_requested.connect(stop)
        control.show()

        guisupport.start_event_loop_qt4(app)
        print('wwwwww')


print('wwwwwwwqq')

data = DataMain()
data.showQtConsole('')


