def RougeN(source: str, target: str, splitChars=' ', N=2) -> float:
    wordDict = {}
    wordDictInv = []
    sourceList = source.split(splitChars)
    targetList = target.split(splitChars)
    currentIdx = 0
    for i in sourceList + targetList:
        if i not in wordDict.keys():
            wordDict[i] = currentIdx
            wordDictInv.append(i)
            currentIdx = currentIdx + 1
    newSource = []
    newTarget = []
    for i in sourceList:
        newSource.append(wordDict[i])
    for i in newTarget:
        newTarget.append(wordDict[i])
    targetMap = {}
    originalMap = {}
    for idx in range(len(newSource) - N + 1):
        phrase = ' '.join(sourceList[idx: idx + N])
        phrase2 = ' '.join(targetList[idx: idx + N])
        if phrase2 not in originalMap.keys():
            originalMap[phrase2] = 1
        else:
            originalMap[phrase2] = originalMap[phrase2] + 1

        if phrase not in targetMap.keys():
            targetMap[phrase] = 1
        else:
            targetMap[phrase] = targetMap[phrase] + 1

    matchedPhrases = 0
    totalPhrases = 0
    for i in originalMap:
        totalPhrases += originalMap[i]
        matchCount = 0
        if i in targetMap.keys():
            matchCount = targetMap[i]
        matchedPhrases += min(matchCount, originalMap[i])
    return 100.0 * matchedPhrases / totalPhrases

def countLCS(list1: list, list2: list) -> int:
    save = 0
    dp = []
    for i in range(min(len(list1), len(list2)) + 7):
        dp.append(0)
    la = max(len(list1), len(list2))
    lb = min(len(list1), len(list2))
    flag = len(list1) > len(list2)
    for i in range(la):
        save = dp[0]
        for j in range(lb):
            k = dp[j + 1]
            if flag and (list1[i] == list2[j]):
                dp[j + 1] = save + 1;
            elif (not flag) and (list1[j] == list2[i]):
                dp[j + 1] = save + 1;
            else:
                dp[j + 1] = max(dp[j], dp[j + 1])
            save = k
    return dp[lb]


def RougeL(source: str, target: str, splitChars=' ', beta=1) -> float:
    wordDict = {}
    wordDictInv = []
    sourceList = source.split(splitChars)
    targetList = target.split(splitChars)
    currentIdx = 0
    for i in sourceList + targetList:
        if i not in wordDict.keys():
            wordDict[i] = currentIdx
            wordDictInv.append(i)
            currentIdx = currentIdx + 1
    newSource = []
    newTarget = []
    for i in sourceList:
        newSource.append(wordDict[i])
    for i in targetList:
        newTarget.append(wordDict[i])
    lcsLen = countLCS(newSource, newTarget)
    Rlcs = 1.0 * lcsLen / len(newSource)
    Plcs = 1.0 * lcsLen / len(newTarget)
    Flcs = 1.0 * (((1.0 + beta * beta) * Rlcs * Plcs) / (Rlcs + beta * beta * Plcs))
    return Flcs
