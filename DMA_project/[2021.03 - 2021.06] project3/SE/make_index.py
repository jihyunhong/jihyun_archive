import os.path
from whoosh.index import create_in
from whoosh.fields import Schema, TEXT, NUMERIC
from nltk.stem import WordNetLemmatizer, PorterStemmer
from nltk.tag import pos_tag as tag
from nltk.tokenize import word_tokenize as wtk
from nltk.corpus import stopwords

schema = Schema(docID=NUMERIC(stored=True), contents=TEXT(stored=True))
index_dir = "index"


if not os.path.exists(index_dir):
    os.makedirs(index_dir)

ix = create_in(index_dir, schema)
# ix = index.open_dir(index_dir)

writer = ix.writer()
lem = WordNetLemmatizer()
stem = PorterStemmer()
stopWords = set(stopwords.words('english'))

with open('doc/document.txt', 'r') as f:
    text = f.read()
    docs = text.split('   /\n')[:-1]
    
    def get_wordnet_pos(tag):
            if tag.startswith('J'):
                return 'a'
            elif tag.startswith('V'):
                return 'v'
            elif tag.startswith('N'):
                return 'n'
            elif tag.startswith('R'):
                return 'r'
            else:
                return 'n'
    
    for doc in docs:
        br = doc.find('\n')
        docID = int(doc[:br])
        doc_text = doc[br+1:]
        tagged_token_list = tag(wtk(doc_text))
        doc_lem_text = ""
        
        for pos in tagged_token_list:
            if pos[0].lower() not in stopWords:
                doc_lem_text += lem.lemmatize(pos[0], pos = get_wordnet_pos(pos[1]))
                doc_lem_text +=' '
        doc_text = doc_lem_text
        writer.add_document(docID=docID, contents=doc_text)

writer.commit()