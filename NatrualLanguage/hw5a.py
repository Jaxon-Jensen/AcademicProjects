'''
import nltk
from nltk.corpus import brown

# Function to search for words and phrases according to tags
def search_corpus(category, search_tag, search_word=None):
    category_words = brown.words(categories=category)
    category_tagged = nltk.pos_tag(category_words)
    results = [word for word, tag in category_tagged if tag == search_tag]
    if search_word:
        results = [word for word in results if search_word in word.lower()]
    return results

# Function to count distinct adjectives tagged with JJ
def count_adjectives(category):
    category_words = brown.words(categories=category)
    category_tagged = nltk.pos_tag(category_words)
    distinct_adjectives = sorted(set(word.lower() for word, tag in category_tagged if tag == 'JJ'))
    return len(distinct_adjectives), distinct_adjectives

# Categories to search
categories = ['humor', 'romance', 'government']

# Search for specific words and phrases according to tags
for category in categories:
    # Search for distinct adjectives tagged with JJ
    num_adjectives, distinct_adjectives = count_adjectives(category)
    
    print(f"\nResults for category: {category.capitalize()}")
    print(f"Number of distinct adjectives (JJ) in {category.capitalize()}: {num_adjectives}")
'''

'''
import nltk
from nltk.corpus import brown

# Function to search for words and phrases according to tags
def search_corpus(category, search_tag, search_word=None):
    category_words = brown.words(categories=category)
    category_tagged = nltk.pos_tag(category_words)
    results = [word for word, tag in category_tagged if tag == search_tag]
    if search_word:
        results = [word for word in results if search_word in word.lower()]
    return results

# Function to identify words that occur as both plural nouns and third person singular verbs
def find_plural_noun_and_third_person_singular_verb(category):
    category_words = brown.words(categories=category)
    category_tagged = nltk.pos_tag(category_words)
    plural_nouns = {word for word, tag in category_tagged if tag == 'NNS'}
    third_singular_verbs = {word for word, tag in category_tagged if tag == 'VBZ'}
    common_words = sorted(plural_nouns.intersection(third_singular_verbs))
    return common_words

# Categories to search
categories = ['humor', 'romance', 'government']

# Search for words that occur as both plural nouns and third person singular verbs
for category in categories:
    common_words = find_plural_noun_and_third_person_singular_verb(category)
    
    print(f"\nResults for category: {category.capitalize()}")
    print("Words that occur as both plural nouns and third person singular verbs:")
    print(", ".join(common_words))
    
    # Find the second element of the sorted list
    if len(common_words) >= 2:
        print(f"The second element of the sorted list is: {common_words[1]}")
    else:
        print("There are not enough common words to find the second element.")
'''


import nltk
from nltk.corpus import brown
from collections import Counter

# Function to identify three-word prepositional phrases of the form IN + DT + NN
def find_three_word_phrases(category):
    category_words = brown.words(categories=category)
    category_tagged = nltk.pos_tag(category_words)
    phrases = []
    all_phrases = []
    for i in range(len(category_tagged) - 2):
        word1, tag1 = category_tagged[i]
        word2, tag2 = category_tagged[i+1]
        word3, tag3 = category_tagged[i+2]
        if tag1 == 'IN' and tag2 == 'DT' and tag3.startswith('NN'):
            phrase = (word1.lower(), word2.lower(), word3.lower())
            phrases.append(phrase)
        all_phrases.append((word1.lower(), word2.lower(), word3.lower()))
    return phrases

# Categories to search
categories = ['humor', 'romance', 'government']

# Search for three-word prepositional phrases
for category in categories:
    phrases = find_three_word_phrases(category)
    phrase_counts = Counter(phrases)

    # Find the most frequent three-word prepositional phrase
    most_common_phrases = phrase_counts.most_common()
    
    if most_common_phrases:  # Check if the list is not empty
        max_count = most_common_phrases[0][1]
        most_frequent_phrases = [(phrase, count) for phrase, count in most_common_phrases if count == max_count]

        # Sort alphabetically to break ties
        most_frequent_phrases.sort(key=lambda x: x[0])

        print(f"\nMost frequent three-word prepositional phrase(s) for {category.capitalize()}:")
        for phrase, count in most_frequent_phrases:
            print(" ".join(phrase), f"- Frequency: {count}")
        
        # Display all three-word prepositional phrases that share the max frequency
        print(f"\nAll three-word prepositional phrases with frequency {max_count} for {category.capitalize()}:")
        for phrase, count in phrase_counts.items():
            if count == max_count:
                print(" ".join(phrase), f"- Frequency: {count}")
    else:
        print(f"No three-word prepositional phrases found in {category.capitalize()}.")





'''
import nltk
from nltk.corpus import brown

# Define masculine and feminine pronouns
masculine_pronouns = ['himself', 'his', 'him', 'he', "he's", "he'd", "he'll"]
feminine_pronouns = ['herself', 'her', 'hers', 'she', "she's", "she'd", "she'll"]

# Define Brown tags for pronouns
pronoun_tags = ['PPL-HL', 'PPO', 'PPS-NC', 'PPS+HVD', 'PP$-NC', 'PPO-TL', 'PPS+BEZ-NC',
                'PPL', 'PPL-NC', 'PPO-NC', 'PPS', 'PP$-TL', 'PPS-HL', 'PP$$', 
                'PPS+BEZ', 'PPS+MD', 'PPS+HVZ', 'PPS-TL', 'PP$']

# Function to count masculine and feminine pronouns
def count_pronouns(category):
    category_tagged = brown.tagged_words(categories=category)
    masculine_count = 0
    feminine_count = 0
    for word, tag in category_tagged:
        if tag in pronoun_tags:
            word_lower = word.lower()
            if word_lower in masculine_pronouns or word in masculine_pronouns:
                masculine_count += 1
            elif word_lower in feminine_pronouns or word in feminine_pronouns:
                feminine_count += 1
    return masculine_count, feminine_count

# Categories to search
categories = ['humor', 'romance', 'government']

# Count masculine and feminine pronouns for each category
for category in categories:
    masculine_count, feminine_count = count_pronouns(category)
    print(f"\n{category.capitalize()}:")
    print(f"Masculine: {masculine_count}")
    print(f"Feminine: {feminine_count}")
'''

'''
import nltk
from nltk.corpus import brown
from collections import defaultdict

# Get tagged words from the Brown Corpus
tagged_words = brown.tagged_words()

# Create a defaultdict to store tags for each word
word_tags = defaultdict(set)

# Populate word_tags dictionary with tags for each word
for word, tag in tagged_words:
    word_tags[word.lower()].add(tag)

# Count the number of distinct words with exactly 5 possible tags
count_words_with_5_tags = sum(1 for tags in word_tags.values() if len(tags) == 5)

print(f"Number of tagged words with exactly 5 possible tags: {count_words_with_5_tags}")
'''

'''
import nltk
from nltk.corpus import brown
from collections import defaultdict

# Get tagged words from the Brown Corpus
tagged_words = brown.tagged_words()

# Create a defaultdict to store the set of tags for each word
word_tag_sets = defaultdict(set)

# Populate word_tag_sets dictionary with tags for each word
for word, tag in tagged_words:
    word_tag_sets[word.lower()].add(tag)

# Create a dictionary to store the count of tags for each word
word_tag_counts = {word: len(tags) for word, tags in word_tag_sets.items()}

# Find the maximum count of tags
max_tag_count = max(word_tag_counts.values())

# Find the words with the maximum count of tags
words_with_max_tags = [word for word, count in word_tag_counts.items() if count == max_tag_count]

# Sort the list of words alphabetically
words_with_max_tags.sort()

# Report the words with the max tags
print(f"The word(s) with the most distinct tags ({max_tag_count} tags) in the Brown Corpus:")
for word in words_with_max_tags:
    print(word)
'''
