from sklearn.datasets import load_files
from sklearn.feature_extraction.text import CountVectorizer, TfidfTransformer
from sklearn import metrics
from sklearn.cluster import KMeans
import nltk
from nltk.corpus import wordnet
nltk.download('wordnet')
nltk.download('stopwords')
nltk.download('averaged_perceptron_tagger')
from nltk.corpus import stopwords
import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('ggplot')
from sklearn.decomposition import PCA

categories = ['opinion', 'business', 'world', 'us', 'arts', 'sports', 'books', 'movies']

data = load_files(container_path='text_all', categories=categories, shuffle=True,
                    encoding='utf-8', decode_error='replace')

# TODO - Data preprocessing and clustering
# dataframe, lower
dataframe = pd.DataFrame(data.data, data.target)
dataframe.columns=['text']

dataframe['text'] = dataframe['text'].str.lower()

# title split & weight
dataframe['text'] = dataframe['text'].str.split('\n')
dataframe2 = dataframe['text'].apply(pd.Series)

dataframe2.columns=['title', 'body', 'NAN']
del dataframe2['NAN']

dataframe2['total'] = (dataframe2['title'] + ' ')*2 + dataframe2['body']

# nomalization (tokenize, pos_tagging, lemmatize)
w_tokenizer = nltk.tokenize.WhitespaceTokenizer()
lemmatizer = nltk.stem.WordNetLemmatizer()

def get_wordnet_pos(treebank_tag):
    if treebank_tag.startswith('J'):
        return wordnet.ADJ
    elif treebank_tag.startswith('V'):
        return wordnet.VERB
    elif treebank_tag.startswith('N'):
        return wordnet.NOUN
    elif treebank_tag.startswith('R'):
        return wordnet.ADV
    else:
        return wordnet.NOUN

def pos_tag(text):
    pos_tokens1 = [nltk.pos_tag(w_tokenizer.tokenize(text))]
    pos_tokens2 = [[(lemmatizer.lemmatize(word, get_wordnet_pos(pos_tag))) for (word, pos_tag) in pos] for pos in pos_tokens1]
    return pos_tokens2[0]

dataframe2['lemma'] = dataframe2.total.apply(pos_tag)

# stopwords remove
sw = stopwords.words('english')
dataframe2['le_st'] = dataframe2['lemma'].apply(lambda x: ' '.join([word for word in x if word not in sw]))

del dataframe2['title']
del dataframe2['body']
del dataframe2['total']
del dataframe2['lemma']

# vectorize
vectorizer = CountVectorizer(stop_words='english',  analyzer='word', min_df=9)
data_trans1 = vectorizer.fit_transform((dataframe2['le_st']))
data_trans2 = TfidfTransformer(smooth_idf=False).fit_transform(data_trans1)

# cluster
clst = KMeans(n_clusters=8, random_state=10)
clst.fit(data_trans2)

print(metrics.v_measure_score(data.target, clst.labels_))