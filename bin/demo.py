#DEMO
import webbrowser, sys, os
import datetime as dt
import scrapers as scrape
###~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
greetings = ["HELLO","HI ","GOOD MORNING","GOOD AFTERNOON", "GOOD EVENING","BYE", "THANK"]
questions = ["WHO ", "WHAT ", "WHICH ", "WHERE ", "WHY ", "WHEN", "HOW ", "IS ", "CAN "]
commands = ["TIME", "WEATHER", "FORECAST", "DATE", "GOOGLE", "BBC", "CNN", "NEWS", "WIKIPEDIA", "CALCULAT", "RECOGNISE", "SAVE", "FOCUS"]
scommands = ["OPEN", "SEARCH", "FIND", "DOWNLOAD", "WIKI", "DEFINE", "PLAY"]    #commands with 'arguments'
progams = ["CALCULATOR", "PYTHON"]

months = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "Novermber", "December"]
numbers = ["ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "TEN"]
week = ["MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"]
ex = False              #python exit flag
imageExitFlag = False   #image recognitio exit flag
qflag = False           #question flag
sflag = False           #specital command flag
state = 0
newname = ""
fileDIR = "./detection1/InputOutput/"     #image-speech communicatio files directory
ERR = "No Internet Connection"
def weekForecast(s):
    today = sysDate('wkd')
    index = 0
    diff = 0
    reqDay = ""
    for i,n in enumerate(week):
        if(n is today):
            index = i
            break
    for i,n in enumerate(week[index:]):
        if(n in s):
            diff = i
            reqDay = n
            break
    if(diff<5):
        try:
            rep = str(scrape.dailyMet(diff))
            msg = reqDay+": "+rep
            print(msg)
            repeat(msg)
        except Exception, e:
            print(ERR)
            repeat(ERR)
    else:
        msg = "Only 5-day forecast available, say open for more."
        print(msg)
        repeat(msg)
#~~~~~~~IMAGE_SPEECH COMMUNIACTION~~~~~~~~~~~~~~~~~~
def readFile():            #input communication file
    fIN = open(fileDIR+"image_to_speech.txt", 'r+')
    line = fIN.readline()
    fIN.seek(0)
    fIN.write('&')
    fIN.close()
    return line
def imageControl():
    c = readFile()
    if(c!='&'):
        print(c)
        global state
        if(c=='1'):     #yes/no mode
            state=4
            return
        if(c=='2'):     #speling mode
            state=3
            return
        if(c=='3'):     #commands+conv mode
            state=0
            return
        if(c=='0'):     #conv mode -> image has exited
            state=0
            imageExitFlag = True
            return
def writeFile(st):            #ouput communication file 
    fOUT = open(fileDIR+"speech_to_image.txt", 'w')
    fOUT.write(st)
    fOUT.close()
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
def getFirst(word):
    temp = word.strip(" ")
    return temp[0]
lflag = False
def stepLogic(st, s):
    global state    #global state
    if(st==1):   #'weather mode'
        print("weather mode")
        if('HELP' in s):
            msg = "Say Open to open bbc weather, or forecast-day for daily forecast. Exit to return."
            print (msg+" (only 4-day forecast available)")
            repeat(msg)
        if('OPEN' in s):
            webbrowser.open('http://www.bbc.co.uk/weather/2643123')
            msg = "opening, bbc weather forecast"
            repeat(msg)
        if('FORECAST' in s):
            weekForecast(s)
        if('EXIT' in s):
            repeat("exiting")
            state=0
            return
    if(st==2):   #'news mode'
        print("News mode")
        num=0
        if('HELP' in s):
            msg = "Use Title, Read, or Open, for a news story. Exit to return."
            print (msg)
            repeat(msg)
        for i,n in enumerate(numbers):
            if (n in s):
                num = i
                break
        if('TITLE' in s):
            try:
                msg = scrape.bbcTopn(num)
                msg1 = msg.replace("'","")
                print (msg1)
                repeat(msg1)
            except Exception, e:
                print(ERR)
                repeat(ERR)
        if('READ' in s):
            try:
                l = scrape.bbcLink(num)
                msg = scrape.storyIntro(l)
                print (msg)
                repeat(msg)
            except Exception, e:
                print(ERR)
                repeat(ERR)
        if('OPEN' in s):
            try:
                l = scrape.bbcLink(num)
                webbrowser.open(l)
                repeat("opening news story")
            except Exception, e:
                print(ERR)
                repeat(ERR)
        if('EXIT' in s):
            repeat("exiting")
            state = 0
            return
    if(st==3):   #spelling mode
        print("Spelling mode")
        bf = False  #backspace flag
        global newname
        if('DONE' in s or 'FINISH' in s):
            writeFile(newname+'$')
            state=0
            return
        if('EXIT' in s or 'CANCEL' in s):
            writeFile(newname+'&')
            newname=""
            state=0
            return
        if('SPACE' in s):
            writeFile(newname+' ')
            bf = True
        if('BACKSPACE' in s or 'DELETE' in s):
            if(len(newname)>0):
                newname=newname[:-1]
                bf = True
            else:
                bf = True
        if(bf==False):
            letter = getFirst(s)
            newname += letter
        print(newname)
        writeFile(newname)
    if(st==4):   #yes/no mode
        print('yes/no mode')
        if('YES' in s):
            writeFile('y')
            state=0
            return
        if('NO' in s):
            writeFile('n')
            state=0
            return
        if('STOP' in s or 'EXIT' in s):
            writeFile('&')
            state=0
            return
    else:
        return
            
def sCom(c,s):      #actions with arguments
    global sflag
    index = s.find(c)
    if(c=='SEARCH'):
        arg = s[(index+7):].strip()
        aarg = arg.replace(" ","+")
        try:
            webbrowser.open('http://www.google.com/search?q='+aarg)
            repeat("searching google, "+aarg)
        except Exception, e:
                print(ERR)
                repeat(ERR)
        sflag = True
    if(c=='WIKI'):
        arg = s[(index+5):]
        aarg = arg.replace(" ","+")
        try:
            webbrowser.open('http://www.wikipedia.org/wiki/'+aarg)
            repeat("searching wikipedia, "+aarg)
        except Exception, e:
                print(ERR)
                repeat(ERR)
        sflag = True
def action(com,s):      #actions following commands
    global state
    if(com==0):     #time
        msg = sysDate('t')
        print (msg)
        repeat(msg)
    if(com==1 or com==2): #weather / forecast
        repeat("Weather mode. Say help for information")
        state = 1
        for d in week:
            if(d in s):
                weekForecast(s)
                break
    if(com==3):     #date
        d = sysDate('d')
        y = sysDate('yr')
        m = int(sysDate('m'))-1
        msg = (months[m] + " " + d + ", " + y)
        print(msg)
        repeat(msg)
    if(com==4):     #google
        try:
            webbrowser.open('http://www.google.com')
            msg = "opening, google"
            print(msg)
            repeat(msg)
        except Exception, e:
                print(ERR)
                repeat(ERR)
    if(com==5):     #bbc
        try:
            webbrowser.open('http://www.bbc.co.uk/news')
            msg = "opening, bbc news"
            print(msg)
            repeat(msg)
        except Exception, e:
                print(ERR)
                repeat(ERR)
    if(com==6):     #cnn
        try:
            webbrowser.open('http://www.cnn.com/world')
            msg = "opening, cnn news"
            print(msg)
            repeat(msg)
        except Exception, e:
                print(ERR)
                repeat(ERR)
    if(com==7):     #news
        if("LIST" in s):
            try:
                repeat("Top four news stories: ")
                msg = str(scrape.bbcTopn(0))
                msg1 = msg.replace("'","")
                print(msg1)
                repeat (msg1)
                msg = str(scrape.bbcTopn(1))
                msg1 = msg.replace("'","")
                print(msg1)
                repeat (msg1)
                msg = str(scrape.bbcTopn(2))
                msg1 = msg.replace("'","")
                print(msg1)
                repeat (msg1)
                msg = str(scrape.bbcTopn(3))
                msg1 = msg.replace("'","")
            except Exception, e:
                print(ERR)
                repeat(ERR)
        else:
            try:
                msg = "Top bbc news story: " + scrape.bbcTop1()
                msg1 = msg.replace("'","")
            except Exception, e:
                print(ERR)
                repeat(ERR)
        print(msg1)
        repeat(msg1)
        state = 2
        repeat("News mode. Say help for information")
    if(com==8):         #wikipedia
        try:
            webbrowser.open('http://www.wikipedia.com')
            msg = "opening, wikipedia"
            print(msg)
            repeat(msg)
        except Exception, e:
                print(ERR)
                repeat(ERR)
    if(com==9):         #calculator
       os.system("galculator")
       repeat("opening calculator")
    if(com==10):        #recognise
        writeFile('r')
    if(com==11):        #save
        print("saving")
        writeFile('s')
    if(com==12):        #focus
        writeFile('c')
def cut(st,n):      #cut number from string
    return st[n:]
def sysDate(req):   #reads and saves current date & time
    wkday = int(dt.datetime.now().weekday())
    wkdays = week[wkday]
    st = str(dt.datetime.now())
    if(req=='wkd'):
        return wkdays
    if(req=='all'):
        return st+" "
    if(req=='yr'):
        return st[0:4]
    if(req=='m'):
        return st[5:7]
    if(req=='d'):
        return st[8:10]+" "+wkdays
    if(req=='t'):
        return st[11:16]
    if(req=='ampm'):                #returns correct greeting
        hour = int(st[11:13])
        if(hour<11 and hour>5):
            return "Good morning master"
        if(hour>13 and hour<18):
            return "Good afternoon master"
        if(hour>22 or hour<5):
            return "Good night master"
        if(hour>18 or hour<22):
            return "Good evening master"
        else:
            return "Hello master"
def repeat(s):
    os.system("./TTS.sh " + "'"+s+"' ")
def scCheck(s):     #check for special command
    global sflag
    sflag = False
    for x in scommands:
        if(x in s):
            sCom(x,s)
            break
def cmdCheck(s):    #check for commands in list
    flag = False
    for i,c in enumerate(commands):
        if (c in s):
            flag = True
            action(i,s)
            return flag
            break
def gCheck(s):      #greeting check
    for g in greetings:
        if (g in s):
            greet(s)
            break
def QCheck(s):      #question check
    global qFlag
    qFlag = False
    for q in questions:
        if (q in s):
            qFlag = True
            quest(s)
            break
def greet(s):       #greeting responses
    if ("BYE"in s):
        msg="Goodbye master"
        print(msg)
        repeat(msg)
    elif ("THANK" in s):
        msg="Your welcome master"
        print(msg)
        repeat(msg)
    else:
        msg = sysDate('ampm')
        print(msg)
        repeat(msg)
def quest(s):       #find subject of question
    if(cmdCheck(s)==True):
        pass
    else:
        if(sflag==False and imageExitFlag==True):
            search = (str(s)).strip()
            ssearch = search.replace(" ","+")
            print("Searching online...")
            msg="searching online"
            repeat(msg)
            webbrowser.open('http://www.google.com/search?q='+ssearch)
        else:
            return
def logic(s):       #RESPONSE LOGIC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    global ex       # exit flag for process.join
    gCheck(s)       #check if greeting
    scCheck(s)
    if(sflag==False):
        QCheck(s)       #check if question
        if(qFlag==False):
            cmdCheck(s)
    if (s== "EXIT" and imageExitFlag == True):
        writeFile("No new input")
        ex = True
        print ("exiting")
        repeat("exiting")   #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    elif(s=="EXIT" or s=="DONE" or s=="QUIT"):
        if(imageExitFlag == False):
            writeFile('&')
            return
def loop():         #MAIN LOOP~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    plast = "begin"
    latest =""
    global state
    while True:
        f=open('stt.txt','r')
        for line in f:
            pass
        last = str(line)
        imageControl()
        if(last==plast):
            continue
        else:
            plast = last
            latest = (cut(last,11)).rstrip()  #strip trailing spaces
            print (latest)                      #latest command
            if(state==0):
                logic(latest)
                stepLogic(state, latest)
            else:
                stepLogic(state, latest)
        if (ex==True):
            break
    f.close()
    sys.exit(1)     #~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
