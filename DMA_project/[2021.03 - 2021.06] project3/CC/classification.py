#!/usr/bin/env python
# coding: utf-8

# In[8]:


from sklearn.datasets import load_files
from sklearn.pipeline import Pipeline
from sklearn import metrics
import numpy as np
import pickle
import os

categories = ['opinion', 'business', 'world', 'us', 'arts', 'sports', 'books', 'movies']

train_data = load_files(container_path='text/train', categories=categories, shuffle=True,
                        encoding='utf-8', decode_error='replace')

# Preprocessing
import pandas as pd
import nltk

def preProcess(documents):  
    news_df = pd.DataFrame({'document':documents})
    # 특수 문자 제거
    news_df['clean_doc'] = news_df['document'].str.replace("[^a-zA-Z]", " ")
    # 길이가 3이하인 단어는 제거 (길이가 짧은 단어 제거)
    news_df['clean_doc'] = news_df['clean_doc'].apply(lambda x: ' '.join([w for w in x.split() if len(w)>3]))
    # 전체 단어에 대한 소문자 변환
    news_df['clean_doc'] = news_df['clean_doc'].apply(lambda x: x.lower())

    return news_df['clean_doc']


# TODO - 2-1-1. Build pipeline for Naive Bayes Classifier
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.naive_bayes import MultinomialNB
clf_nb = Pipeline([('vect', CountVectorizer(stop_words = 'english')),
                   ('tfidf', TfidfTransformer(use_idf=True)),
                   ('clf', MultinomialNB(alpha=0.05))])
clf_nb.fit(preProcess(train_data.data), train_data.target)

# TODO - 2-1-2. Build pipeline for SVM Classifier
from sklearn.svm import SVC
from sklearn.svm import LinearSVC
clf_svm = Pipeline([('vect', CountVectorizer(stop_words='english')),
                   ('tfidf', TfidfTransformer()),
                    ('clf', SVC(C = 1, gamma = 1, kernel = 'linear'))])
clf_svm.fit(preProcess(train_data.data), train_data.target)


test_data = load_files(container_path='text/test', categories=categories, shuffle=True,
                       encoding='utf-8', decode_error='replace')
docs_test = test_data.data

predicted = clf_nb.predict(docs_test)
print("NB accuracy : %d / %d" % (np.sum(predicted==test_data.target), len(test_data.target)))
print(metrics.classification_report(test_data.target, predicted, target_names=test_data.target_names))
print(metrics.confusion_matrix(test_data.target, predicted))

predicted = clf_svm.predict(docs_test)
print("SVM accuracy : %d / %d" % (np.sum(predicted==test_data.target), len(test_data.target)))
print(metrics.classification_report(test_data.target, predicted, target_names=test_data.target_names))
print(metrics.confusion_matrix(test_data.target, predicted))

TEAM = 6

with open('DMA_project3_team%02d_nb.pkl' % TEAM, 'wb') as f1:
    pickle.dump(clf_nb, f1)

with open('DMA_project3_team%02d_svm.pkl' % TEAM, 'wb') as f2:
    pickle.dump(clf_svm, f2)


# In[ ]:




