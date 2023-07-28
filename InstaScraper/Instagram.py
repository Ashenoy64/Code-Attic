#imports
from datetime import datetime
from itertools import dropwhile, takewhile
import instaloader
import csv
import os


class Instagram:
    usernames=["hackerearth"]
    downloadPath=None
    userPosts=[]
    csvPath="instagram.csv"
    start=datetime(2023, 1, 20)
    end=datetime(2023, 1, 26)
    def __init__(self):
        pass

    def setUsernames(self,usernames):
        self.usernames=usernames

    def setDate(self,start,end):
        self.start=datetime(year=start[0],month=start[1],day=start[2])
        self.end=datetime(year=end[0],month=end[1],day=end[2])

    def setDownloadLocation(self,path):
        self.downloadPath=path+"/InstaFolder/{target}"

    def getPosts(self):
        L = instaloader.Instaloader(dirname_pattern=self.downloadPath)
        for user in self.usernames:
            # print(user)
            posts = instaloader.Profile.from_username(L.context,user).get_posts()
            for post in takewhile(lambda p: p.date >=self.start, dropwhile(lambda p: p.date >=self.end, posts)):
                obj=[]
                # print(post)
                obj.append(user)
                obj.append(post.mediaid)
                obj.append(post.url)
                obj.append(post.caption_hashtags)    
                obj.append(post.caption)
                self.userPosts.append(obj)
                if(self.downloadPath!=None):
                    L.download_post(post,target=user)


    def setCsvPath(self,path):
        self.csvPath=path
    def writeCsv(self):
        fields = ["Name","ID","URL","Tags","Caption"]
        with open(self.csvPath, 'w') as csvfile:    
            csvwriter = csv.writer(csvfile)
            csvwriter.writerow(fields)
            csvwriter.writerows(self.userPosts)    

    def iDontKnowPython(self):
        print("Hello Dumb user")
        
        print("Set The path Of Downloads")
        path=input("Enter The path:")
        if(path!=""):
            self.setDownloadLocation(path)

        print("Set CSV path")
        path=input("Enter the Path:")
        if(path!=""):
            self.setDownloadLocation(path)

        print("Enter The Target Username:")
        l=input().split(" ")
        self.setUsernames(l)

        print("Set Start Date")
        sY=int(input("Enter The start Year:"))
        sM=int(input("Enter The start Month:"))
        sD=int(input("Enter The start Day:"))

        print("Set The End Date")
        eY=int(input("Enter The end Year:"))
        eM=int(input("Enter The end Month:"))
        eD=int(input("Enter The end Day:"))

        self.setDate([sY,sM,sD],[eY,eM,eD])

        self.getPosts()
        self.writeCsv()


if __name__=="__main__":
    obj=Instagram()
    # print(os.getcwd())
    obj.setDownloadLocation(os.getcwd())
    obj.getPosts()
    obj.writeCsv()



