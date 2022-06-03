"OI"
function compress(originalImg, k)
  image = imread(originalImg);
  p = size(image)(1)
  n = (p + k)/(1+k)
  p = n + (n-1)*k;
  #image;
  solution = zeros(n,n,3);
  indices = [1 ];
  for i = 1:p
    if(mod(i, k+1) == 0)
      indices = [indices i];
    endif
  endfor
  ii = 1
  jj = 1
  for i = indices
    for j = indices
      solution(ii,jj,:) = image(i,j,:);
      jj = jj + 1
    endfor
    jj = 1
    ii = ii + 1
  endfor

  imwrite(solution, "/home/luizz/Documents/materias/MAC0210/ep2/anime2.jpg")

  indices;

  solution
endfunction

compress("/home/luizz/Documents/materias/MAC0210/ep2/anime.jpg",2)
