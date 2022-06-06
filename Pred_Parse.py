grammer = {
	"E":["TB"],
	"B":["+TB","e"],
    "T":["FY"],
    "Y":["*FY", "e"],
	"F":["(E)","id"]
}

def remLR(grammerA, A):
	temp = grammerA[A]
	tempCr = []
	t = []
	for i in temp:
		if i[0] == A:
			t.append(i[1:] + [A + "'"])
		else:
			tempCr.append(i + [A + "'"])

	t.append(["e"])
	grammerA[A] = tempCr
	grammerA[A + "'"] = t
	return grammerA


def chk(grammerA, a, ai):
	if ai not in grammerA:
		return False
	if a == ai:
		return True
	for i in grammerA[ai]:
		if i[0] == ai:
			return False
		if i[0] in grammerA:
			return chk(grammerA, a, i[0])
			
	return False

def rep(grammerA, A):
	temp = grammerA[A]
	newTemp = []
	for i in temp:
		if chk(grammerA, A, i[0]):
			t = []
			for k in grammerA[i[0]]:
				t=[]
				t+=k
				t+=i[1:]
				newTemp.append(t)

		else:
			newTemp.append(i)
	grammerA[A] = newTemp
	return grammerA

def rem(grammer):
	c = 1
	conv = {}
	grammerA = {}
	revconv = {}
	for j in grammer:
		conv[j] = "A"+str(c)
		grammerA["A"+str(c)] = []
		c+=1

	for i in grammer:
		for j in grammer[i]:
			temp = []
			for k in j:
				if k in conv:
					temp.append(conv[k])
				else:
					temp.append(k)
			grammerA[conv[i]].append(temp)


	#print(grammerA)
	for i in range(c-1,0,-1):
		ai = "A"+str(i)
		for j in range(0,i):
			aj = grammerA[ai][0][0]
			if ai!=aj :
				if aj in grammerA and chk(grammerA,ai,aj):
					grammerA = rep(grammerA, ai)

	for i in range(1,c):
		ai = "A"+str(i)
		for j in grammerA[ai]:
			if ai==j[0]:
				grammerA = remLR(grammerA, ai)
				break

	op = {}
	for i in grammerA:
		a = str(i)
		for j in conv:
			a = a.replace(conv[j],j)
		revconv[i] = a

	for i in grammerA:
		l = []
		for j in grammerA[i]:
			k = []
			for m in j:
				if m in revconv:
					k.append(m.replace(m,revconv[m]))
				else:
					k.append(m)
			l.append(k)
		op[revconv[i]] = l

	return op

result = rem(grammer)
terminals = []
for i in result:
	for j in result[i]:
		for k in j:
			if k not in result:
				terminals+=[k]
terminals = list(set(terminals))

def first(grammer, term):
	a = []
	if term not in grammer:
		return [term]
	for i in grammer[term]:
		if i[0] not in grammer:
			a.append(i[0])
		elif i[0] in grammer:
			a += first(grammer, i[0])
	return a

firsts = {}
for i in result:
	firsts[i] = first(result,i)

def follow(grammer, term):
	a = []
	for rule in grammer:
		for i in grammer[rule]:
			if term in i:
				temp = i
				indx = i.index(term)
				if indx+1!=len(i):
					if i[-1] in firsts:
						a+=firsts[i[-1]]
					else:
						a+=[i[-1]]
				else:
					a+=["e"]
				if rule != term and "e" in a:
					a+= follow(grammer,rule)
	return a

follows = {}
for i in result:
	follows[i] = list(set(follow(result,i)))
	if "e" in follows[i]:
		follows[i].pop(follows[i].index("e"))
	follows[i]+=["$"]
#	print(f'Follow({i}):',follows[i])

resMod = {}
for i in result:
	l = []
	for j in result[i]:
		temp = ""
		for k in j:
			temp+=k
		l.append(temp)
	resMod[i] = l

# create predictive parsing table
tterm = list(terminals)
tterm.pop(tterm.index("e"))
tterm+=["$"]
pptable = {}
for i in result:
	for j in tterm:
		if j in firsts[i]:
			pptable[(i,j)]=resMod[i[0]][0]
		else:
			pptable[(i,j)]=""
	if "e" in firsts[i]:
		for j in tterm:
			if j in follows[i]:
				pptable[(i,j)]="e"

pptable[("F","i")] = "i"
toprint = f'{"": <10}'
for i in tterm:
	toprint+= f'|{i: <10}'
print(toprint)
for i in result:
	toprint = f'{i: <10}'
	for j in tterm:
		if pptable[(i,j)]!="":
			toprint+=f'|{i+"->"+pptable[(i,j)]: <10}'
		else:
			toprint+=f'|{pptable[(i,j)]: <10}'
	print(f'{"-":-<76}')
	print(toprint)