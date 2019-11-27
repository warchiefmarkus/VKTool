import os
import sys
import pandas as pd

#import numpy as np
#from PythonQt.QtGui import *
#from PythonQt import *

#writer = pd.ExcelWriter('QQQQQ.xlsx', engine='xlsxwriter')
#df.to_excel(writer, sheet_name='Stations')
#writer.save()

class DataMain():
    def __init__(self, fileName = None):
        filename = None

    # Parsing members list from cpp by Pandas to separated lists to use it in qml from cpp
    def parse(self, jsonString):
       final = jsonString
       self.data = pd.DataFrame.from_records(final)

    def filter(self, sex, online, country, city, bdate, name):
        #df.query('(first_name == "Татьяна")&(sex == 1)')

        #sex
        df = self.data.query('(sex =='+sex+')')
        #online
        if(online!='3'):
            df = df.query('(online =='+online+')')
        #country
        if(country!='0'):
            df = df.query('(country =='+country+')')
        #city
        if(city!='0'):
            df = df.query('(city =='+city+')')


        return df['first_name'].astype(str).tolist(), df['last_name'].astype(str).tolist(), df['id'].astype(str).tolist(), df['photo_100'].astype(str).tolist(), df['photo_50'].astype(str).tolist(), df['photo_id'].astype(str).tolist(), df['sex'].astype(str).tolist(), df['bdate'].astype(str).tolist(), df['city'].astype(str).tolist(), df['country'].astype(str).tolist(), df['last_seen'].astype(str).tolist()



#df.query('(first_name == "Татьяна")&(sex == 1)')




