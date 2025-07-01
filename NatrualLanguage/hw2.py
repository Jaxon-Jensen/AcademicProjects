'''from nltk.corpus import gutenberg
text = gutenberg.sents('austen-sense.txt')
print(len(text))'''


'''from nltk.book import *
text1.concordance('suit')
    #Is it the case that word "suit" is used with different meanings  across the two texts?'''

'''from nltk.corpus import brown
import nltk as nk
genres = ['news', 'religion', 'hobbies', 'science_fiction', 'romance', 'humor']
modals = ['green', 'white', 'blue', 'red', 'yellow', 'purple']
nk.ConditionalFreqDist((genre,word) for genre in brown.categories() for word in brown.words(categories=genre)).tabulate(conditions=genres, samples=modals)
    table of modal distributions'''

'''from nltk.corpus import wordnet as wn
empty = 0
total = 0
for ss in wn.all_synsets('n'):
    if len(ss.hyponyms()) == 0:
        empty += 1
    total += 1
print(empty/total)
    What percentage of noun synsets have no hyponyms?'''

from nltk.corpus import brown
from nltk import *
import nltk.corpus
stopwords = nltk.corpus.stopwords.words('english')
print(stopwords)
'''content = list(bigrams([w for w in brown.words() if w.lower() not in stopwords and w.isalpha()]))
fdist = FreqDist(content)
print(fdist.most_common(5))
    #5 most frequent bigrams (pairs of adjacent tokens) of a text (given as a list of tokens), omitting bigrams that contain stopwords and punctuation.'''

'''from nltk.corpus import wordnet as wn
count = 0
all_nouns = set([word for synset in wn.all_synsets('n') for word in synset.lemma_names()])

for n in all_nouns:
    count += len(wn.synsets(n, 'n'))

print(count/len(all_nouns))

#all_verbs = [word for synset in wn.all_synsets('v') for word in synset.lemma_names()]
#for v in all_verbs:
    #count += len(wn.synsets(v))
    #total += 1'''