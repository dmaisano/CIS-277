% Classifier for the iris data set. There are 3 types if iris.
% The data set contains 50 samples from from each of 3 types of iris.
% Each row contains 4 floating point numbers giving various measurements
% of the flower, and the fifth number is the iris type (1, 2, or 3).
% The classifier classifies a sample as "Type 1" or "Not type 1".

C = csvread('Iris.txt',0,0);

A = C(C(:,5)>1.5,:);
B = C(C(:,5)<1.5,:);

i = 1;
j = 2;

        scatter(A(:,i), A(:,j), 5, 'd')
        hold on
        scatter(B(:,i), B(:,j))

% Use first two attributes

%PlusInput = csvread('wdbcMalig.txt',0,1);
%MinusInput = csvread('wdbcBenign.txt',0,1);

PlusInput = A(:,[i j]);
MinusInput = B(:,[i j]);
[p1 q1] = size(PlusInput)
[p2 q2] = size(MinusInput)
%set training size vs. test size
q = q1; %number of variables
p = 30; %number of malig. training
r = 30; %number of benign training
Ain = PlusInput(1:p,:);
Bin = MinusInput(1:r,:);
size(Ain)
size(Bin)

A = [-Ain, ones(p,1), -eye(p,p),zeros(p,r);
    Bin, -ones(r,1), zeros(r,p), -eye(r,r);
    zeros(p,q), zeros(p,1), -eye(p,p), zeros(p,r);
    zeros(r,q), zeros(r,1), zeros(r,p), -eye(r,r)];


c = [zeros(1,q), zeros(1,1), (1.0/p)*ones(1,p), (1.0/r)*ones(1,r)]';
%c = [zeros(1,q), zeros(1,1), ones(1,p+r)]';
b =[-ones(1,p+r), zeros(1,p+r)]';

lps = linprog(c,A,b);


w = lps(1:q);
gma = lps(q+1);

w

gma

hline = refline([-w(1)/w(2)  (gma+1.0)/w(2)]);
hline.Color = 'g';
hline = refline([-w(1)/w(2)  gma/w(2)]);
hline.Color = 'r';
hline = refline([-w(1)/w(2)  (gma-1.0)/w(2)]);
hline.Color = 'b';


size(w)
size(PlusInput(1,:))
mcorrect = 0;
for i=p+1 : p1
    if((w')*PlusInput(i,:)' > gma +1.0)
        mcorrect = mcorrect + 1;
    end;
end;


'proportion correct='
mcorrect/(p1-p)

bcorrect = 0;
for i=r+1 : p2
    if((w')*MinusInput(i,:)' < gma -1.0)
        bcorrect = bcorrect + 1;
    end;
end;

'proportion correct='
bcorrect/(p2-r)
