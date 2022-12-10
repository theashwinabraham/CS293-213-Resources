import sys
import random

numOfNodes = int(sys.argv[2])

file = open(sys.argv[3], "w")

if sys.argv[4] == "BST":
    file.write("0\n")
else:
    file.write("1\n")

perComparisonCost = int(sys.argv[5])
perParentChildUpdateCost = int(sys.argv[6])
file.write(f"{perComparisonCost}\n")
file.write(f"{perParentChildUpdateCost}\n")

if sys.argv[1] == "sorted":
    for i in range(numOfNodes):
        print(f"ADD {i+10} {(i*2)%1000}\n")
        file.write(f"ADD {i+10} {(i*2)%1000}\n")

        # Uncomment the following lines if you want to test DEL
        # delFlag = random.choice(range(5))
        # if (delFlag == 1):
        #     rand = random.choice(range(i+1))
        #     print(f"DEL {rand+10}\n")
        #     file.write(f"DEL {rand+10}\n")
            
    for i in range(numOfNodes):
        rand = random.choice(range(numOfNodes))
        print(f"FIND {rand+10}\n")
        file.write(f"FIND {rand+10}\n")

elif sys.argv[1] == "reverse":
    for i in range(numOfNodes)[::-1]:
        print(f"ADD {i+10} {(i*2)%1000}\n")        
        file.write(f"ADD {i+10} {(i*2)%1000}\n")

        # Uncomment the following lines if you want to test DEL
        # delFlag = random.choice(range(5))
        # if (delFlag == 1):
        #     rand = random.choice(range(i+1))
        #     print(f"DEL {rand+10}\n")
        #     file.write(f"DEL {rand+10}\n")
            
    for i in range(numOfNodes):
        rand = random.choice(range(numOfNodes))
        print(f"FIND {rand+10}\n")
        file.write(f"FIND {rand+10}\n")

elif sys.argv[1] == "random":
    lists = list(range(numOfNodes))
    random.shuffle(lists)
    for i in lists:
        print(f"ADD {i+10} {(i*2)%1000}\n")        
        file.write(f"ADD {i+10} {(i*2)%1000}\n")

        # Uncomment the following lines if you want to test DEL
        # delFlag = random.choice(range(5))
        # if (delFlag == 1):
        #     rand = random.choice(range(i+1))
        #     print(f"DEL {rand+10}\n")
        #     file.write(f"DEL {rand+10}\n")
            
    for i in range(numOfNodes):
        rand = random.choice(range(numOfNodes))
        print(f"FIND {rand+10}\n")
        file.write(f"FIND {rand+10}\n")

file.close()
