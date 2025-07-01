import requests
from bs4 import BeautifulSoup
from collections import Counter
import nltk
from nltk.tokenize import word_tokenize

def get_text_from_url(url):
    try:
        response = requests.get(url)
        if response.status_code == 200:
            soup = BeautifulSoup(response.text, 'html.parser')
            # Find all text elements
            text_elements = soup.find_all(string=True)
            # Concatenate text elements into a single string
            text = ' '.join(element.strip() for element in text_elements if element.strip())
            return text
        else:
            print(f"Failed to retrieve content from {url}. Status code: {response.status_code}")
            return None
    except Exception as e:
        print(f"An error occurred: {e}")
        return None

def novel10(text):
    words = word_tokenize(text.lower())  # Tokenize and convert to lowercase
    total_words = len(words)
    word_counts = Counter(words)
    
    last_10_percent = int(total_words * 0.1)
    novel_words = set()
    
    for word in words[-last_10_percent:]:
        if word_counts[word] == 1:
            novel_words.add(word)
            
    novel_words_sorted = sorted(novel_words)  # Sort the novel words alphabetically
    
    print("Novel words in the last 10% of the text:")
    for i in range(0,10):
        print(novel_words_sorted[i])


def shorten(text, n):
    # Tokenize text and convert to lowercase
    words = word_tokenize(text.lower())
    
    # Count the frequency of each word
    word_counts = Counter(words)
    
    # Determine the n most frequent words
    most_common_words = [word for word, _ in word_counts.most_common(n)]
    
    # Filter out the most frequent words
    filtered_words = [word for word in words if word not in most_common_words]
    
    # List of omitted words
    omitted_words = [word for word in most_common_words if word in text.lower()]
    
    # Join the filtered words back into a string
    shortened_text = ' '.join(filtered_words)
    
    return shortened_text, omitted_words


if __name__ == "__main__":
    url = "https://www.cs.utexas.edu/~vl/notes/dijkstra.html"
    text = get_text_from_url(url)
    if text:
        novel10(text)
    else:
        print("Failed to retrieve text from the URL.")

    text2 = "to begin with I would like to thank the College of Natural Sciences for the most honouring Invitation to address its newest flock of Bachelors on this most festive day. I shall do my best."
    n = 20
    shortened_text, omitted_words = shorten(text, n)
    print("Original text:")
    print(text2)
    print("\nShortened text (omitting", n, "most frequent words):")
    print(shortened_text)
    print("\nList of omitted words:")
    print(omitted_words)
