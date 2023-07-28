from datetime import datetime
from itertools import dropwhile, takewhile

import instaloader

L = instaloader.Instaloader()

posts = instaloader.Profile.from_username(L.context, "hackerearth").get_posts()
print("done")
SINCE = datetime(2023, 5, 1)
UNTIL = datetime(2023, 1, 20)
l=[]
for post in takewhile(lambda p: p.date > UNTIL, dropwhile(lambda p: p.date > SINCE, posts)):
    print(post.date)
    l.append(post)
    L.download_post(post, "./new/hackereart")


for i in l:
    print(i.url,"\n",i.mediaid,"\n",i.caption_hashtags,"\n ---------------------\n")