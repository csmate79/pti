def leet(text):
    getchar = lambda c: chars[c] if c in chars else c
    chars = {"a":"4","e":"3","o":"0","s":"5","E":"3","A":"4","O":"0","t":"7","T":"7"}
    return ''.join(getchar(c) for c in text)
szoveg = input ("Szöveg: ")
print(leet(szoveg))
