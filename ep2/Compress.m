"OI"
function compress(originalImg, k)
  image = imread(originalImg);
  p = size(image)(1)
  n = (p + k)/(1+k)
  p = n + (n-1)*k;
  #image;
  solution = zeros(n);
  ii = 0;
   for i = 1:p
    for j = 1:p
      if(i == mod(0,k+1))
        solution(i-ii)(j-ii) = image(1)(i)(j);
      else
        ii++;
      endif
    endfor
  endfor



  solution
endfunction

compress("/home/luizz/Documents/materias/MAC0210/ep2/anime.jpg",2)
