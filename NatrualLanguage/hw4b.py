'''from nltk.corpus import wordnet as wn

def sort_synsets_by_distance(synset, synsets):
    return sorted(synsets, key=lambda s: synset.shortest_path_distance(s))

# Given synsets
minke_whale = wn.synset('minke_whale.n.01')
orca = wn.synset('orca.n.01')
novel = wn.synset('novel.n.01')
tortoise = wn.synset('tortoise.n.01')
right_whale = wn.synset('right_whale.n.01')

# List of synsets to be sorted
synsets_to_sort = [minke_whale, orca, novel, tortoise]

# Sort the synsets based on their shortest path distance to 'right_whale'
sorted_synsets = sort_synsets_by_distance(right_whale, synsets_to_sort)

# Report the sorted synsets
print(sorted_synsets)
'''

from urllib.request import urlopen
from bs4 import BeautifulSoup
from nltk.tokenize import sent_tokenize, word_tokenize
from nltk.probability import FreqDist

def extractive_summarization(text, n):
    # Normalize the text by converting it to lowercase
    normalized_text = text.lower()
    
    # Tokenize the text into sentences
    sentences = sent_tokenize(normalized_text)
    
    # Tokenize the text into words
    words = word_tokenize(normalized_text)
    
    # Count the frequency of each word across the document
    word_freq = FreqDist(words)
    
    # Calculate the total word frequency for each sentence
    sentence_scores = []
    for sentence in sentences:
        sentence_words = word_tokenize(sentence)
        score = sum(word_freq[word] for word in sentence_words)
        sentence_scores.append((sentence, score))
    
    # Rank the sentences based on their total word frequency
    ranked_sentences = sorted(sentence_scores, key=lambda x: x[1], reverse=True)
    
    # Mark the top n highest-scoring sentences
    top_n_sentences = set([sentence for sentence, _ in ranked_sentences[:n]])
    
    # Print the top n highest-scoring sentences in document order
    for sentence in sentences:
        if sentence in top_n_sentences:
            print(sentence + "\n\n")

# Retrieve the testText
html = urlopen('https://www.cs.utexas.edu/~vl/notes/dijkstra.html').read().decode('utf-8')
testText = BeautifulSoup(html,'html.parser').get_text()

# Run the extractive summarization function with n=7 and show the output
extractive_summarization(testText, 6)
