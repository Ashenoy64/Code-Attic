import email
from email import message
import instaloader
import smtplib

gmail_user='testm7078@gmail.com'
gmail_password='shenoy@72'
sent_from=gmail_user
to=["ashenoy64@gmail.com"]
subject="Instagram Followers"
body=""
print("If your account is Private then either you need to give your account details or follow 'pokemon_master_abs'")
wish=input("Yes if your gonna provide the details No if your gonna follow the account:")
if wish.lower()=='no':
    USER=""
    PASSWORD=""
    User=input("Your account user name:")
else:
    USER=input("Enter the username:")
    PASSWORD=input("Enter your password")
    User=USER
loader=instaloader.Instaloader()

loader.login(USER, PASSWORD)
profile=instaloader.Profile.from_username(loader.context,User)
followers_iterator=profile.get_followers()
followers=set()
for f in followers_iterator:
    followers.add(f.username)
following=set()
for i in profile.get_followees():
    following.add(i.username)

cheaters=following-followers
for i in cheaters:
    print(i)
    body=body+i+'\n'
print("No of cheaters:",len(cheaters))   
email_text="""\
    From:%s
    To:%s
    Subject:%s
    %s"""%(sent_from,",".join(to),subject,body)

try:
    smtp=smtplib.SMTP('smtp.gmail.com',587)
    smtp.starttls()
    smtp.login(sent_from,gmail_password)    

    message=email_text

    smtp.sendmail(sent_from,to[0],message)
    smtp.quit()
    print("email sent succesfully")
except Exception as ex:
    print(ex)
n=input()