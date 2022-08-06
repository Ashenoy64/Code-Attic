import os

from bs4 import BeautifulSoup



def update():

        os.system("pip install cloudscraper -U")
import cloudscraper

scraper=cloudscraper.create_scraper()
def download(url):
    a=scraper.get(url)
    data=a.text
    soup=BeautifulSoup(data,"lxml")

    m_info=(soup.find("iframe"))
    try:

        os.system("""start brave "{}" """.format(m_info["src"][2:]))
    except:
        os.system("""start edge "{}" """.format(m_info["src"][2:]))


def search():
        search_item=input("Enter movie name: ")
        search_item=search_item.replace(" ","%20")
        a=scraper.get("https://vidembed.io/search.html?keyword={}".format(search_item))
        data=a.text
        soup=BeautifulSoup(data,"lxml")

        a_lis=[]
        count=1
        video_data=soup.find_all("li",class_="video-block")
        if len(video_data)!=0:

                for i in video_data:
                    name=i.find("div",class_="name")
                    print(count,")",(name.text).strip())
                    url=i.find("a",href=True)
                    a_lis.append(url["href"])
                    count+=1
                print(count,")Back")
                choice=input(">> ")
                if choice.isdigit():
                    try:
                        if int(choice)!=count and int(choice)<count:

                                download("https://vidembed.io{}".format(a_lis[int(choice)-1]))
                        elif int(choice)==count:
                            return
                        else:
                            print("invalid input 1")

                    except:
                        print("Print invalid input")
                else:
                    print("invalid input")
        else:
            print("Nothing found")




while True:
            print("""
                   -+#%@%%#+-
                .+%#=-=#%%%%%%+. --
               -%%#     +%%%%@%%+ -%+.
              +%%%+      %%=. .+%%::%%=
             -%%%%#     :@:     -%%:.%%+
            .%%-.:#%=::=%%       @%% :%%=
            +%-    %%%%%%%=     :%%%* *%%.
            %%:    *%%*+%#%+.  :#%%%@ .@%=                     .-+%%###%%#*+=-.
            %%*   .%%=#-#+%%%%%%%%%%%: #%*                  :=#%*=.      -*%%%%%*=:
            %%%#==#%%%* =**%%=.  -%%%- +%#              .-*%%%+.     .-*%%*=: :+##+#*-
            +%%%#-:=%*#**%%%+      %%-=-=+            =#*=%#-+#%%*=*%%*=.        :+%%+#*-
            .%%%.   .%%%#%%@-      *@. *#:           +%: =%.    :+%+%+:             -+*%%%*-
             =%%     #%#=-=##      #*:-=-#*.        =%==#%-        =%=*#=.             -#=-#%=.
              +%+   :%%     *#-..-#%.:%*+##%=      :@#+*@=           +%#=#+.          .-+%%%%%#*-
               +%%*#%%+     :%%%%%%: -.#%. :%#:   .%*:*#:             .+**%%+.    :=+%%%%%%#*#--%#=
                -%%%%%%     =%%%%#: *%- *%*%#=##=-%%%#=                 :##.+%==*%%%%%%%*-.   +%%%%%-
                 .+%%%%#:..=%%%%=  **:   +%%-.=%%%+-.                     +%#%%%%%@#+-.        :#%-:**
                    :+#%%@%%#+-   :.      .-*#%#+.                         :#%-+%#.              -%#%#
                                                                             +#=#%%-               =%#
                                                                              -%%*+%+               .=
                                                                               .**.-%#.
                                                                                 =%%%%%-
            .                                                ..

            ___  ___           _            ______                    _                 _
            |  \/  |          (_)           |  _  \                  | |               | |
            | .  . | _____   ___  ___  ___  | | | |_____      ___ __ | | ___   __ _  __| | ___ _ __
            | |\/| |/ _ \ \ / / |/ _ \/ __| | | | / _ \ \ /\ / / '_ \| |/ _ \ / _` |/ _` |/ _ \ '__|
            | |  | | (_) \ V /| |  __/\__ \ | |/ / (_) \ V  V /| | | | | (_) | (_| | (_| |  __/ |
            \_|  |_/\___/ \_/ |_|\___||___/ |___/ \___/ \_/\_/ |_| |_|_|\___/ \__,_|\__,_|\___|_|





            """)
            choice=input("""1)Update (Use this if search does not work)
2) Search movies
3) Exit
>>>""")
            if choice.isdigit():

                    if int(choice)==1:
                        update()
                    elif int(choice)==2:
                        search()
                    elif int(choice)==3:
                        break
                    else:
                        print("invalid input")
            else:
                print("invalid input")
