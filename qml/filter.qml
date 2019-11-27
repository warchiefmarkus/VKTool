import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0



Item{
    id: filter

    signal showFilter(string sex, string online, string country, string city, string bdate, string name)

    Column{
        spacing: 15
        ComboBox {
            id: sex
            width: filter.width
            model: ["Wooman","Man"]
        }
        ComboBox {
            id: online
            width: filter.width
            model: ["","Online","OFF"]
        }
        ComboBox {
            id: country
            width: filter.width
            model: ["","Russia","Ukraine"]
        }
        ComboBox {
            id: city
            width: filter.width
            model: ["","Kiev"] // Kiev 314
        }
        TextInput {
            id: bdate
            height: country.height
            color: "red"
            width: filter.width
        }
        TextInput{
            id: name
            height: country.height
            color: "red"
            width: filter.width
        }

        Button{
            width: filter.width
            height: 50
            text: "SHOW"
            onClicked: {

                var psex;
                var ponline;
                var pcountry;
                var pcity;
                var pbdate;
                var pname;

                // sex
                switch(sex.currentIndex){
                case 0:
                    //filter.showFilter(1);
                    psex = 1;
                    break;
                case 1:
                    psex = 2;
                    break;
                default:
                    break;
                }

                // online
                switch(online.currentIndex){
                case 0:
                    //filter.showFilter(1);
                    ponline = 3;
                    break;
                case 1:
                    ponline = 1;
                    break;
                case 2:
                    ponline = 0;
                    break;
                default:
                    break;
                }

                // country
                switch(country.currentIndex){
                case 0:
                    pcountry = 0;
                    break;
                case 1:
                    pcountry = 1;
                    break;
                case 2:
                    pcountry = 2;
                    break;
                default:
                    break;
                }

                // city
                switch(city.currentIndex){
                case 0:
                    pcity = 0;
                    break;
                case 1:
                    pcity = 314; //kiev
                    break;
                default:
                    break;
                }

                console.log("PRE FILTER ")
                filter.showFilter(psex,ponline,pcountry,pcity,pbdate,pname)
            }
        }
    }
}
