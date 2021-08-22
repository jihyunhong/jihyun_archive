import whoosh.index as index
from whoosh.qparser import QueryParser, OrGroup
from whoosh import scoring
import CustomScoring as scoring
from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize as tk
from nltk.tag import pos_tag as tag
from nltk.stem import WordNetLemmatizer, PorterStemmer
from nltk.corpus import wordnet as wn
import numpy as np

def getSearchEngineResult(query_dict):
    modify_result_dict = {}
    first_result_dict = {}
    ix = index.open_dir("index")
    lem = WordNetLemmatizer()
    stem = PorterStemmer()
    # with ix.searcher(weighting=scoring.BM25F(B=0.8)) as searcher:
    with ix.searcher(weighting=scoring.ScoringFunction()) as searcher:

        # TODO - Define your own query parser
        parser = QueryParser("contents", schema=ix.schema, group=OrGroup.factory(0.5))
        stopWords = set(stopwords.words('english'))
        
        def get_wordnet_pos(tag):
            if tag.startswith('J'):
                return ('a','t')
            elif tag.startswith('V'):
                return ('v','t')
            elif tag.startswith('N'):
                return ('n','t')
            elif tag.startswith('R'):
                return ('r','t')
            else:
                return ('n','f')

        for qid, q in query_dict.items():
            new_q = ''
            tagged_list = tag(tk(q))
            lemmed_list =[]
            weighted_token = []


            for i, pos in enumerate(tagged_list):

                tagged = get_wordnet_pos(pos[1])
                word_lem = lem.lemmatize(pos[0], pos = tagged[0])

                if pos[0].lower() not in stopWords:
                    lemmed_list.append([word_lem, tagged])

                if word_lem.lower() not in stopWords:
                    if tagged == ('n','t') :
                        weighted_token.append(word_lem+'^1.1')

                    elif tagged[0] == 'a' or tagged[0] == 'j':
                        if get_wordnet_pos(tagged_list[i-1][1]) == ('n','t') or get_wordnet_pos(tagged_list[i+1][1]) == ('n','t'):
                            weighted_token.append(word_lem+'^1.1')
                        elif get_wordnet_pos(tagged_list[i-2][1]) == ('n','t'):
                            weighted_token.append(word_lem + '^1.06')
                        else:
                            weighted_token.append(word_lem)

                    else:
                        weighted_token.append(word_lem)

            for word in weighted_token:
                new_q += word + ' '

            first_query = parser.parse(new_q.lower())
            results = searcher.search(first_query, limit=None)
            

            keywords = [keyword for keyword, score
                        in results.key_terms("contents", docs=10, numterms=7)]
            add_keyword_query = new_q

            for word in keywords:
                add_keyword_query += ' '+ word+'^0.35'

            
            new_bi = ''
            bigram = [word[0] for word in lemmed_list]
            bigram_2 = list(zip(bigram, bigram[1:]))   
            bigram_3 = ['\"' + ' '.join(word) + '\"' for word in bigram_2]

            for word in bigram_3:
                new_bi += ' '+word+'^0.3'

            add_keyword_query +=  ' ' + new_bi

            query = parser.parse(add_keyword_query.lower())
            modify_results = searcher.search(query,limit = None)


            modify_result_dict[qid] = [result.fields()['docID'] for result in modify_results]

    return modify_result_dict