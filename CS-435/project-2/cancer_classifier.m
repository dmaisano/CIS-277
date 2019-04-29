% Domenico Maisano
% CS 435 Section 002

%{
==== Instructions to run program ====

To run the classifier program, please type the following:

matlab -nodisplay -nodesktop -r "run cancer_classifier.m"

To run the program and save the output to a text file, type the following:

matlab -nodisplay -nodesktop -r "run cancer_classifier.m" > result.txt
%}


%{
==== Dual of Program ====

The current program is designed to find an optimization for the two given sets of data,
where we are given our objective to find the minimization of the equation (1/p) SIGMA(yi) + (1/r) SIGMA (zj)...
along with the inequality constraints for both y and z, as well as the bounds for y and z (greater than or equal to zero)

The dual of the program would instead be designed to do the opposite of what is currently implemented, and would seek to find the max of the given initial given equation
%}


PlusInput = csvread('wdbcMalig.txt',0,1);
MinusInput = csvread('wdbcBenign.txt',0,1);

[p1 q1] = size(PlusInput)
[p2 q2] = size(MinusInput)

%set training size vs. test size
q = q1;  % number of variables (30)
p = 100; % number of malig. training
r = 200; % number of benign training

Ain = PlusInput(1:p,:);
Bin = MinusInput(1:r,:);
size(Ain)
size(Bin)

A = [-Ain, ones(p,1), -eye(p,p),zeros(p,r);
    Bin, -ones(r,1), zeros(r,p), -eye(r,r);
    zeros(p,q), zeros(p,1), -eye(p,p), zeros(p,r);
    zeros(r,q), zeros(r,1), zeros(r,p), -eye(r,r)];


c = [zeros(1,q), zeros(1,1), ones(1,p+r)]';
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


'proportion malignant correct='
mcorrect/(p1-p)

bcorrect = 0;
for i=r+1 : p2
    if((w')*MinusInput(i,:)' < gma -1.0)
        bcorrect = bcorrect + 1;
    end;
end;

'proportion benign correct='
bcorrect/(p2-r)

% exit when done
exit
