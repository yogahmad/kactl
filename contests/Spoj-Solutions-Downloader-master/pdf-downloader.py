import urllib2,os
from urllib2 import urlopen

import httplib2
from BeautifulSoup import BeautifulSoup, SoupStrainer

username = 'yusufsholeh'

url = 'http://www.spoj.com/users/' + username + '/'

def download_problem(prblm):

    if len(prblm) < 1 :
        return
    
    url = 'http://www.spoj.com/problems/'
    prblm = prblm.upper()
    url = url + prblm +'.pdf'
    print('Downloading '+url)
    pdf = urllib2.urlopen(url)
    #if int(pdf.info().getheader('Content-Length').strip())<=10:
    #	print 'Error downloading '+prblm
    #	exit()
    output = open(prblm+'.pdf','wb')
    output.write(pdf.read())
    pdf.close()
    print('Done')



import lxml.html

doc = lxml.html.parse(urlopen(url))

links = doc.xpath('//a[@href]')

for link in links:
    if 'status' in str(link.attrib['href']) and ','+username in str(link.attrib['href']):
        prblem = link.attrib['href'][8:-13]
        download_problem(prblem)

