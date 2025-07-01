from nltk.book import *
import re

pattern = r'\b(?:what|where|when|which|who|whom|whose|why)\b'
txt = " ".join(text7)
matches = re.findall(pattern, txt, re.IGNORECASE)
print(len(matches))


'''from nltk.corpus import brown

# Load the mystery section of the Brown Corpus
mystery_words = brown.words(categories='mystery')
mystery_sents = brown.sents(categories='mystery')

# Calculate the average word length
total_characters = sum(len(word) for word in mystery_words)
total_words = len(mystery_words)
average_word_length = total_characters / total_words

# Calculate the average sentence length
total_words_in_sentences = sum(len(sent) for sent in mystery_sents)
total_sentences = len(mystery_sents)
average_sentence_length = total_words_in_sentences / total_sentences

# Calculate the Automated Readability Index (ARI)
ari = 4.71 * average_word_length + 0.5 * average_sentence_length - 21.43

# Print the results
print(f"Average word length in the Mystery section: {average_word_length:.2f} characters")
print(f"Average sentence length in the Mystery section: {average_sentence_length:.2f} words")
print(f"Automated Readability Index (ARI) in the Mystery section: {ari:.4f}")
'''


'''import nltk
from nltk.corpus import abc
from nltk.tokenize import word_tokenize, sent_tokenize

# Obtain raw texts for ABC Rural News and ABC Science News
rural_raw_text = abc.raw('rural.txt')
science_raw_text = abc.raw('science.txt')

# Tokenize the text into words
rural_words = word_tokenize(rural_raw_text)
science_words = word_tokenize(science_raw_text)

# Tokenize the text into sentences using Punkt
rural_sentences = sent_tokenize(rural_raw_text)
science_sentences = sent_tokenize(science_raw_text)

# Calculate average word length for each category
average_word_length_rural = sum(len(word) for word in rural_words) / len(rural_words)
average_word_length_science = sum(len(word) for word in science_words) / len(science_words)

# Calculate average sentence length for each category
average_sentence_length_rural = len(rural_words) / len(rural_sentences)
average_sentence_length_science = len(science_words) / len(science_sentences)

# Calculate ARI scores for each category
ari_rural = 4.71 * average_word_length_rural + 0.5 * average_sentence_length_rural - 21.43
ari_science = 4.71 * average_word_length_science + 0.5 * average_sentence_length_science - 21.43

# Print the results
print(f"Average word length in ABC Rural News: {average_word_length_rural:.2f} characters")
print(f"Average sentence length in ABC Rural News: {average_sentence_length_rural:.2f} words")
print(f"ARI score for ABC Rural News: {ari_rural:.4f}\n")

print(f"Average word length in ABC Science News: {average_word_length_science:.2f} characters")
print(f"Average sentence length in ABC Science News: {average_sentence_length_science:.2f} words")
print(f"ARI score for ABC Science News: {ari_science:.4f}\n")

# Compare ARI scores and determine which category has a greater ARI score
if ari_rural > ari_science:
    print("ABC Rural News has a greater ARI score.")
elif ari_science > ari_rural:
    print("ABC Science News has a greater ARI score.")
else:
    print("Both categories have the same ARI score.")
'''