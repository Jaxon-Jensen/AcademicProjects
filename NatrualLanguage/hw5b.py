'''
import nltk
from nltk.corpus import brown
from nltk.stem import WordNetLemmatizer
from collections import Counter

# Load the Brown Corpus
nltk.download('brown')
nltk.download('wordnet')

# Tokenize and tag the Brown Corpus
tagged_words = brown.tagged_words()

# Initialize a lemmatizer
lemmatizer = WordNetLemmatizer()

# Dictionary to store counts of plural nouns and their corresponding singular forms
noun_counts = {}

# Iterate through tagged words
for word, tag in tagged_words:
    if tag == 'NNS':  # Check if the word is a plural noun
        singular_form = lemmatizer.lemmatize(word, pos='n')  # Get the singular form
        noun_counts[word] = noun_counts.get(word, 0) + 1  # Increment count for plural form
        noun_counts[singular_form] = noun_counts.get(singular_form, 0)  # Initialize count for singular form

# Filter out words where plural form is more common
plural_more_common = {word: count for word, count in noun_counts.items() if noun_counts[word] > noun_counts.get(lemmatizer.lemmatize(word, pos='n'), 0)}

# Sort the dictionary by counts in descending order
sorted_plural_more_common = sorted(plural_more_common.items(), key=lambda x: x[1], reverse=True)

# Print the top 5 words along with their singular forms and counts
print("Top 5 plural nouns more common in plural form than singular form:")
for word, count in sorted_plural_more_common[:5]:
    singular_form = lemmatizer.lemmatize(word, pos='n')
    print(f"Plural: {word} (Singular: {singular_form}) - Count: {count}")
'''



'''
import nltk
from collections import Counter

# Load the Brown Corpus
brown_corpus = nltk.corpus.brown

# Get tagged words from the Brown Corpus
tagged_words = brown_corpus.tagged_words()

# Count the occurrences of each tag
tag_counts = Counter(tag for word, tag in tagged_words)

# Get the 5 most frequent tags in order of decreasing frequency
most_frequent_tags = tag_counts.most_common(5)

# Print the 5 most frequent tags
print("The 5 most frequent tags and their frequencies:")
for tag, count in most_frequent_tags:
    print(f"{tag}: {count}")

# Report the fourth most frequent tag
fourth_most_frequent_tag = most_frequent_tags[3][0]
print("\nThe fourth most frequent tag is:", fourth_most_frequent_tag)
'''

import nltk
from nltk.corpus import brown
from collections import Counter

# Download Brown Corpus if not already downloaded
nltk.download('brown')

# Function to find the third most frequent tag excluding AT and punctuation tags
def find_third_most_frequent_tag_excluding_AT_and_punctuation(category):
    tagged_words = brown.tagged_words(categories=category)
    # Filter out AT and punctuation tags
    filtered_tags = [tag for word, tag in tagged_words if tag not in ['.', ',', ':', '(', ')', '--', '``', "''"]]
    tag_counts = Counter(filtered_tags)
    # Get the third most frequent tag
    third_most_frequent_tag = list(tag_counts.keys())[2]
    return third_most_frequent_tag

# Report the third most frequent tag for humor excluding AT and punctuation tags
third_most_frequent_tag_humor = find_third_most_frequent_tag_excluding_AT_and_punctuation('humor')
print("The third most frequent tag in the 'humor' category (excluding AT and punctuation tags) is:", third_most_frequent_tag_humor)

# Report the third most frequent tag for romance excluding AT and punctuation tags
third_most_frequent_tag_romance = find_third_most_frequent_tag_excluding_AT_and_punctuation('romance')
print("The third most frequent tag in the 'romance' category (excluding AT and punctuation tags) is:", third_most_frequent_tag_romance)

# Report the third most frequent tag for government excluding AT and punctuation tags
third_most_frequent_tag_government = find_third_most_frequent_tag_excluding_AT_and_punctuation('government')
print("The third most frequent tag in the 'government' category (excluding AT and punctuation tags) is:", third_most_frequent_tag_government)




'''
from nltk.corpus import wordnet

# Get all word forms (lemmas) in WordNet
word_forms = wordnet.all_lemma_names()

# Counter for words with senses in multiple categories
words_with_multiple_senses = 0

# Counter for total number of words
total_words = 0

# Iterate over each word form
for word_form in word_forms:
    # Get synsets (senses) associated with the word form
    synsets = wordnet.synsets(word_form)
    
    # Check if the synsets cover multiple POS categories
    pos_categories = set(s.pos() for s in synsets)
    
    # If the synsets cover more than one POS category, increment the counter
    if len(pos_categories) > 1:
        words_with_multiple_senses += 1
    
    # Increment total word count
    total_words += 1

# Calculate the percentage of words with senses in multiple categories
percentage_words_with_multiple_senses = (words_with_multiple_senses / total_words) * 100

print("Percentage of words from the WordNet corpus with senses in more than one category:", percentage_words_with_multiple_senses)
'''