#all internet-related functions
import os, requests, metoffer, webbrowser, re
from mechanize import Browser
from bs4 import BeautifulSoup
ERR = "No Internet Connection"
def repeat(s):
    os.system("./TTS.sh " + "'"+s+"' ")
    
#~~~~~~BBC request~~~~~~~~~~~~~~~~~~~
def bbcNews():
    url = "http://www.bbc.co.uk/news"
    try:
        response = requests.get(url)
        html = response.content
        soup = BeautifulSoup(html, "html.parser")
        item = soup.find_all(class_="title-link__title-text")
        return(item)
    except Exception, e:
        raise
def bbcBuz():
    try:
        url = "http://www.bbc.co.uk/news"
        response = requests.get(url)
        html = response.content
        soup = BeautifulSoup(html, "html.parser")
        item = soup.find(class_="buzzard__summary").text
        return(item)
    except Exception, e:
        raise
#~~~~~metOffice~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def met():  #retrieve 5-day information
    key = '568fbf63-75c5-451e-a282-1388c877e60b'
    try:
        M = metoffer.MetOffer(key)
        x = M.nearest_loc_forecast(53.4840, -2.2440, metoffer.THREE_HOURLY)
        y = metoffer.parse_val(x)
        weatherData = [y.name]      #weather forecast data
        for i in y.data:
            a = ("{}-{}".format(i["timestamp"][0].strftime("%D %b, %H:%M"), metoffer.WEATHER_CODES[i["Weather Type"][0]])+" "+str(i["Temperature"][0]))
            weatherData.append(a)
        return weatherData
    except Exception, e:
        return 0
def dailyMet(day):  #process information into temperature and weather
    try:
        raw = met()
        l = len(raw)
        tot = 0
        today = int(str(raw[1])[3:5])+day
        today = str(today)
        todayForecast = []
        for i in range(l):
            if(str(raw[i])[3:5] == today):
                todayForecast.append(raw[i])
        lf = len(todayForecast)
        for i in range(lf):
            tot += int(todayForecast[i][-2:])
        avgT = tot/lf
        typ = todayForecast[4][20:-3]
        msg1 = "Average Temperature: "+str(avgT)+" degrees. \n"
        msg2 = "Weather Forecast: "+typ +". "
        return(msg1+msg2)
    except Exception, e:
        raise
#~~~~~~BBC news~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def bbcTopn(n):     #top n news story titles
    try:
        news = bbcNews()
        return (news[n].text)
    except Exception, e:
        return 0
def bbcTop1():      #top story title and summary
    try:
        news = bbcNews()
        title = news[0].text
        summary = bbcBuz()
        return(title)
    except Exception, e:
        raise
def bbcLink(n):     #return link for story n
    try:
        url = "http://www.bbc.co.uk/news"
        response = requests.get(url)
        html = response.content
        soup = BeautifulSoup(html, "html.parser")
        item = soup.find_all('a', class_="title-link")
        story = item[n]
        link = "http://www.bbc.co.uk"+story.get('href')
        return link
    except Exception, e:
        return 0

def storyIntro(link):
    try:
        url = link
        response = requests.get(url)
        html = response.content
        soup = BeautifulSoup(html, "html.parser")
        intro = soup.find(class_=re.compile("story-body__introduction")).text
        return (intro)
    except Exception, e:
        raise
#~~~~~NEW DICTIONARY~~~~~~~~~~~~~~~~~~~~~~~~~
def newDict():
    f1=".dic"
    f2=".lm"
    f3=".sent"
    f4=".vocab"
    f5=".log_pronounce"
    name="3145"
    d="/home/pi/pocketsphinx-0.8/src/programs/"
    try:
        br = Browser()
        br.open("http://www.speech.cs.cmu.edu/tools/lmtool-new.html")
        br.select_form(nr=0)
        br.form.add_file(open('corp.txt'), 'text/plain', 'corp')
        response = br.submit()
        url = str(response.geturl())
        content = str(response.read())
        index = content.find("TAR")+3
        compFile = "TAR"+content[index:index+8]
        num=content[index:index+4]
        DL = url+compFile
        os.system("sudo wget "+DL)
        os.system("sudo tar zxf "+compFile+" -C "+d)
        os.system("sudo rm "+compFile)
        os.system("sudo mv "+d+num+f1+" "+d+name+f1)
        os.system("sudo mv "+d+num+f2+" "+d+name+f2)
        os.system("sudo mv "+d+num+f3+" "+d+name+f3)
        os.system("sudo mv "+d+num+f4+" "+d+name+f4)
        os.system("sudo mv "+d+num+f5+" "+d+name+f5)
        print("DONE (3145)")
    except Exception, e:
        print(ERR)
        repeat(ERR)
