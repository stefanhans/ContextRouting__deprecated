#!/bin/bash

cd /home/stefan/Development/ContextRouting/github_repo

# Qt
find ../workspace/Prototypes/ContextClientPrototype_B -mtime 0 -type f \( -name '*.h' -o -name '*.cpp' -o -name '*.pdf' \) -exec cp {} ContextClientPrototype \; 
find ../workspace/Prototypes/TestNetwork -mtime 0 -type f \( -name '*.h' -o -name '*.cpp' \) -exec cp {} ContextGatewayTestClient \; 
find ../workspace/Prototypes/SpatialCodingTestClient -mtime 0 -type f \( -name '*.h' -o -name '*.cpp' \) -exec cp {} SpatialCodingTestClient \; 
find ../workspace/Prototypes/MatrixCodingTestClient -mtime 0 -type f \( -name '*.h' -o -name '*.cpp' \) -exec cp {} MatrixCodingTestClient \;
find ../workspace/Prototypes/MatrixCodingClient -mtime 0 -type f \( -name '*.h' -o -name '*.cpp' \) -exec cp {} MatrixCodingClient \;
find /home/stefan/Development/ContextRouting/workspace/Prototypes/CodingModuleTestClient -mtime 0 -type f \( -name '*.h' -o -name '*.cpp' \) -exec cp {} CodingModuleTestClient \;

# Matrices
find /home/stefan/Development/ContextRouting/Matrices -mtime 0 -type f -name '*_matrix' -exec cp {} Matrices \;

# C/C++
find ../workspace/ContextOfferClient -mtime 0 -type f \( -name '*.cpp' -o -name '*.h' \) -exec cp {} ContextOfferClient \;
find ../workspace/ContextRequestClient -mtime 0  -type f \( -name '*.cpp' -o -name '*.h' \) -exec cp {} ContextRequestClient \;
find ../workspace/LocalContextServer -mtime 0 -type f \( -name '*.cpp' -o -name '*.h' \) -exec cp {} LocalContextServer \;
find /home/stefan/Development/ContextGateway/workspace/ContextGateway_1 -mtime 0 -type f \( -name '*.cpp' -o -name '*.h' -o -name '*.pdf' \) -exec cp {} ContextGateway \;

# RFC
find /home/stefan/RFC/Work -type f -name DraftRFC_ContextRouting.txt -mtime 0 -exec cp {} RFC \;
find /home/stefan/RFC/Work -type f -name DraftRFC_CIP_Specification.txt -mtime 0 -exec cp {} RFC \;
find /home/stefan/RFC/Work -type f -name DraftRFC_CIR_Specification.txt -mtime 0 -exec cp {} RFC \;

# XSD
find /home/stefan/Development/ContextRouting/data/XSD -type f -name '*.xsd' -mtime 0 -exec cp {} XSD \;

# Workshop with Nikita
#find /home/stefan/Development/PrototypeWorkshop/workspace/CRN-Device -mtime 0 -type f \( -name '*.cpp' -o -name '*.h' \) -exec cp {} PrototypeWorkshop \;
find /home/stefan/Development/Test/PrototypeWorkshop/workspace/CRN_Gateway -mtime 0 -type f \( -name '*.cpp' -o -name '*.h' \) -exec cp {} PrototypeWorkshop/Test/CRN_Gateway \;
find /home/stefan/Development/PrototypeWorkshop/LaTex -mtime 0 -type f \( -name '*.pdf' \) -exec cp {} PrototypeWorkshop \;
find /home/stefan/Development/PrototypeWorkshop/UML -mtime 0 -type f \( -name '*.pdf' \) -exec cp {} PrototypeWorkshop \;

for d in CI CIP CRN CRN-Shell
do
 find /home/stefan/Development/PrototypeWorkshop/QtWorkspace/$d -mtime 0 -type f \( -name '*.cpp' -o -name '*.h' \) -exec cp {}  PrototypeWorkshop/Qt/$d \;
done

# local
git add PrototypeWorkshop CodingModuleTestClient ContextClientPrototype ContextOfferClient ContextRequestClient LocalContextServer ContextGateway ContextGatewayTestClient SpatialCodingTestClient MatrixCodingTestClient MatrixCodingClient RFC XSD Matrices
git commit -a

# git pull ContextRouting master

# remote
echo "uni@stefan-hans.de"
echo "St...4e...+1"
git push ContextRouting master


