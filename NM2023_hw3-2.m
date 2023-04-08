#nm2023 hw3-2 by r11944043

function spd = genSPD (n) # by Daryl at https://math.stackexchange.com/questions/357980/how-to-generate-random-symmetric-positive-definite-matrices-using-matlab
  spd = rand(n);
  spd = 0.5 * (spd+spd');
  spd = spd + n * eye(n);
  end

function res = noLoop (A, n)
  for i = 1:n
    A(i,i) = sqrt(A(i,i));
    A(i+1:end, i) = A(i+1:end, i)/A(i,i);
    A(i+1:end, i+1:end) = A(i+1:end, i+1:end) - A(i+1:end, i)*A(i+1:end, i)';
  endfor
  res = tril(A);
end

function res = oneLvLoop (A, n)
  for i = 1:n
    A(i,i) = sqrt(A(i,i));
    A(i+1:end, i) = A(i+1:end, i)/A(i,i);
    for j = i+1:n
      A(j:end, j) = A(j:end, j) - A(j:end, i)*A(j,i);
    endfor
  endfor
  res = tril(A);
end

function res = twoLvLoop (A, n)
  for i = 1:n
    A(i,i) = sqrt(A(i,i));
    A(i+1:end, i) = A(i+1:end, i)/A(i,i);
    for j = i+1:n
      for k = j:n
        A(k, j) = A(k, j) - A(k, i)*A(j,i);
      endfor
    endfor
  endfor
  res = tril(A);
end



A = genSPD(10);
B = genSPD(100);
C = genSPD(1000);
D = genSPD(4000);

#computing 10*10 matrices
printf("computing 10*10 SPD matrix\n")
tic();
rightL = chol(A, "lower");
chtTime = toc();

tic();
L = noLoop(A, 10);
tnTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result noLoop(10*10) is equal to chol() function!\n")
end

tic();
L = oneLvLoop(A, 10);
toTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result oneLvLoop(10*10) is equal to chol() function!\n")
end

tic();
L = twoLvLoop(A, 10);
ttTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result twoLvLoop(10*10) is equal to chol() function!\n")
end

printf('\n\ncomputing 100*100 SPD matrix\n');
#computing 100*100 matrices
tic();
rightL = chol(B, "lower");
chhTime = toc();

tic();
L = noLoop(B, 100);
hnTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result noLoop(100*100) is equal to chol() function!\n")
end

tic();
L = oneLvLoop(B, 100);
hoTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result oneLvLoop(100*100) is equal to chol() function!\n")
end

tic();
L = twoLvLoop(B, 100);
htTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result twoLvLoop(100*100) is equal to chol() function!\n")
end


printf("\ncomputing 1000*1000 SPD matrix\n")
#computing 1000*1000 matrices
tic();
rightL = chol(C, "lower");
chthTime = toc();

tic();
L = noLoop(C, 1000);
thnTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result noLoop(1000*1000) is equal to chol() function!\n")
end

tic();
L = oneLvLoop(C, 1000);
thoTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result oneLvLoop(1000*1000) is equal to chol() function!\n")
end

tic();
L = twoLvLoop(C, 1000);
thtTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result twoLvLoop(1000*1000) is equal to chol() function!\n")
end

printf("\ncomputing 4000*4000 SPD matrix\n")
#computing 4000*4000 matrices
tic();
rightL = chol(D, "lower");
chfTime = toc();

tic();
L = noLoop(D, 4000);
fnTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result noLoop(4000*4000) is equal to chol() function!\n")
end


tic();
L = oneLvLoop(D, 4000);
foTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result oneLvLoop(4000*4000) is equal to chol() function!\n")
end

tic();
L = twoLvLoop(D, 4000);
ftTime = toc();
if(abs(L - rightL) <= 1e-8)
  printf("result twoLvLoop(4000*4000) is equal to chol() function!\n")
end

#comparing elapsed time
fprintf('different elapsed time of computing 10*10 matrix\n    No Loop: %d\n    One level loop: %d\n    Two level loop: %d\n\n', tnTime, toTime, ttTime);
fprintf('different elapsed time of computing 100*100 matrix\n    No Loop: %d\n    One level loop: %d\n    Two level loop: %d\n\n', hnTime, hoTime, htTime);
fprintf('different elapsed time of computing 1000*1000 matrix\n    No Loop: %d\n    One level loop: %d\n    Two level loop: %d\n\n', thnTime, thoTime, thtTime);
fprintf('different elapsed time of computing 4000*4000 matrix\n    No Loop: %d\n    One level loop: %d\n    Two level loop: %d\n\n', fnTime, foTime, ftTime);
