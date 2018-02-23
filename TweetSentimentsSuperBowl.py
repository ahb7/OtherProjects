# -*- coding: utf-8 -*-
"""
Fetch Tweets about "Super Bowl" and analyze their sentiments.

"""
import tweepy
from tweepy import OAuthHandler
import pandas as pd
import numpy as np

#form IPython.display import display
import matplotlib.pyplot as plt
import seaborn as sns
#%matplotlib inline
from textblob import TextBlob
import re

def clean_tweet(tweet):
    '''
    Clean the tweets by removing links and special characters using regex.
    '''
    return ' '.join(re.sub("(@[A-Za-z0-9]+)|([^0-9A-Za-z \t])|(\w+:\/\/\S+)", " ", tweet).split())

def analyze_sentiment(tweet):
    analysis = TextBlob(clean_tweet(tweet))
    if analysis.sentiment.polarity > 0:
        return 1
    elif analysis.sentiment.polarity == 0:
        return 0
    else:
        return -1

consumer_key = 'AzpUqN9jw1KupuMFIcEMxZDxP'
consumer_secret = 'H6RcmT54CQ59J4ozAhw6smFBm2XBzMOOhvGA7NiI2RqX4o9Gp3'
access_token = '963331960046325760-TU608o1SbOP60aopv6UULF8fFOQKias'
access_secret = 'LC6dYMInS8jOOy6t8lBR3TdhPgw2juFTomsEZzqKqOyiI'
 
auth = OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)
 
api = tweepy.API(auth)
#tweets = api.user_timeline(screen_name="realDonaldTrump", count=500)
# Fetch the latest twwets about Super Bowl  
tweets = tweepy.Cursor(api.search, q='super bowl')
tweets.pages(100)
#print("Number of tweets fetched: ", (len(tweets)))

data = pd.DataFrame(columns=['Tweets', 'len', 'ID', 'Date', 'Source', 'Likes', 'RTs'])
for t in tweets.items():   
    row = pd.Series(data= [t.text, len(t.text), t.id, t.created_at, t.source, t.favorite_count, t.retweet_count], \
                           index=['Tweets', 'len', 'ID', 'Date', 'Source', 'Likes', 'RTs'])
    data = data.append(row, ignore_index=True)
    
print(data.head(10))

mean = np.mean(data['len'])
print("\nThe average length of the tweets ", mean)

fav_max = np.max(data['Likes'])
rt_max = np.max(data['RTs'])

fav = data[data.Likes == fav_max].index[0]
rt = data[data.RTs == rt_max].index[0]

# Max FAVs:
print("The tweet with more likes is: \n", data['Tweets'][fav])
print("Number of likes: ", fav_max)

# Max RTs:
print("The tweet with more retweets is: \n", data['Tweets'][rt])
print("Number of retweets: ", rt_max)

tlen = pd.Series(data=data['len'].values, index=data['Date'])
tfav = pd.Series(data=data['Likes'].values, index=data['Date'])
tret = pd.Series(data=data['RTs'].values, index=data['Date'])

tlen.plot(figsize=(16, 4), color='r')
# Likes vs retweets visualization:
tfav.plot(figsize=(16,4), label="Likes", legend=True)
tret.plot(figsize=(16,4), label="Retweets", legend=True);

sources = []
for source in data['Source']:
    if source not in sources:
        sources.append(source)
        
for source in sources:
    print("* {}".format(source))

percent = np.zeros(len(sources))
for source in data['Source']:
    for index in range (len(sources)):
        if source == sources[index]:
            percent[index] +=1
            break
percent /= 100

pie_chart = pd.Series(percent, index=sources, name="Sources")
pie_chart.plot.pie(fontsize=11, autopct='%.2f', figsize=(6,6))

data['SA'] = np.array([analyze_sentiment(tweet) for tweet in data['Tweets']])
print(data.head(10))

pos_tweets = [ tweet for index, tweet in enumerate(data['Tweets']) if data['SA'][index] > 0]
neu_tweets = [ tweet for index, tweet in enumerate(data['Tweets']) if data['SA'][index] == 0]
neg_tweets = [ tweet for index, tweet in enumerate(data['Tweets']) if data['SA'][index] < 0]

print("Percentage of positive tweets: {}%".format(len(pos_tweets)*100/len(data['Tweets'])))
print("Percentage of neutral tweets: {}%".format(len(neu_tweets)*100/len(data['Tweets'])))
print("Percentage de negative tweets: {}%".format(len(neg_tweets)*100/len(data['Tweets'])))

