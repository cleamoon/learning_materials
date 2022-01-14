with open('/usr/share/dict/words', 'r') as dict:
    print("Please input the correct letters without space:")
    inputLetters = list(set([l.lower() for l in list(input())]))
    availableLetters = inputLetters + ["v", "k", "q", "j", "x", "z"]
    feasibleWords = list(filter(lambda word: len(word) == 5 and word.isalpha(), dict.read().lower().splitlines()))
    for word in feasibleWords:
        if len(list(filter(lambda letter: letter.lower() not in availableLetters, word))) == 0:
            if len(set(filter(lambda letter: letter.lower() in inputLetters, word))) == len(inputLetters):
                print(word.upper())
