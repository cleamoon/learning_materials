def feasible(word):
    return len(word) == 5 and word.isalpha() and len(word) == len(word.encode()) and len(set(list(word))) == 5

with open('/usr/share/dict/words', 'r') as dict:
    distinctWords = [w.lower() for w in list(filter(lambda word: feasible(word), dict.read().lower().splitlines()))]
    lessOftenLetters = ["v", "k", "q", "j", "x", "z"]
    words = list(filter(lambda word: len(set(list(word) + lessOftenLetters)) == len(lessOftenLetters) + 5, distinctWords))
    for w1 in words:
        if len(set(list(w1))) != 5:
            continue
        for w2 in words:
            if len(set(list(w1 + w2))) != 10:
                continue
            for w3 in words:
                if len(set(list(w1 + w2 + w3))) != 15:
                    continue
                for w4 in words:
                    if len(set(list(w1 + w2 + w3 + w4))) != 20:
                        continue
                    print(w1 + " " + w2 + " " + w3 + " " + w4)