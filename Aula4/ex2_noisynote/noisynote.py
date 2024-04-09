#############################################
# Exercício 1 - Aula 4 - PSI5790           #
# Nome: Jean Carlos Mello Xavier Faria     #
# Nusp: 11259628                           #
#############################################

import numpy as np
from sklearn import tree
from sklearn import neighbors as nb

def le(nomearq):
    with open(nomearq,"r") as f: 
        linhas=f.readlines()
    linha0=linhas[0].split()
    nl=int(linha0[0]); nc=int(linha0[1])
    a=np.empty((nl,nc),dtype=np.float32)
    for l in range(nl):
        linha=linhas[l+1].split()
        for c in range(nc):
            a[l,c]=np.float32(linha[c])
    return a

ax = le("ax.txt")
ay = le("ay.txt")
qx = le("qx.txt")
qy = le("qy.txt")

error_vector = []

############################################################### kNN ###############################################################

for i in range(1,10):
    vizinho = nb.KNeighborsClassifier(n_neighbors=i, weights="uniform", algorithm="ball_tree", )
    vizinho.fit(ax,ay.ravel())
    qp = vizinho.predict(qx)

    erros = 0

    for i in range(qp.shape[0]):
        if qp[i]!=qy[i]: 
            erros+=1
    error_vector.append(erros)

error_idx = np.argmin(error_vector) + 1

print("Melhor parâmetro de vizinho = %d\n" %(error_idx))

print("Erros utilizando kNN = %d/%d. Pct = %1.3f%%\n"%(error_vector[error_idx-1],qp.shape[0],100.0*error_vector[error_idx-1]/qp.shape[0]))

########################################################### Decision Tree ###########################################################

arvore= tree.DecisionTreeClassifier(splitter="random", random_state=0)
arvore= arvore.fit(ax, ay)
qp=arvore.predict(qx)

erros = 0
for i in range(qp.shape[0]):
    if qp[i]!=qy[i]: 
        erros+=1
        
print("Erros utilizando Decision Tree = %d/%d. Pct = %1.3f%%\n"%(erros,qp.shape[0],100.0*erros/qp.shape[0]))