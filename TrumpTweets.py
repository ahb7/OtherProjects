# -*- coding: utf-8 -*-
"""
Print 25 latest tweets of Donald Trump

"""

import tweepy
from tweepy import OAuthHandler

consumer_key = 'AzpUqN9jw1KupuMFIcEMxZDxP'
consumer_secret = 'H6RcmT54CQ59J4ozAhw6smFBm2XBzMOOhvGA7NiI2RqX4o9Gp3'
access_token = '963331960046325760-TU608o1SbOP60aopv6UULF8fFOQKias'
access_secret = 'LC6dYMInS8jOOy6t8lBR3TdhPgw2juFTomsEZzqKqOyiI'
 
auth = OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)
 
api = tweepy.API(auth)

# Fetch 25 latest twwets of Donald Trump
tweets = api.user_timeline(screen_name="realDonaldTrump", count=25)
print("Number of tweets fetched: {}.\n".format(len(tweets)))

# Print the tweets
print("25 latest tweets:\n")
for tweet in tweets[:25]:
    print(tweet.text)
    print("\n")