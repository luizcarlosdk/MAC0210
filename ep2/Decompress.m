"Oi"
function decompress(compressedImg, method, k, h)
  image = imread(compressedImg);
  n = size(image)(1);
  p = n + (n-1)*k;

  solution = zeros(p,p,3);
  indices = [1 ];
  for i = 1:p
    if(mod(i, k+1) == 0)
      indices = [indices i];
    endif
  endfor
ii= 1
jj= 1
  for i = indices
    for j = indices
      solution(i,j,:) = image(ii,jj,:);
      jj = jj + 1;
    endfor
    jj = 1;
    ii = ii + 1;
  endfor

  imwrite (uint8(solution), "decompressed.png", "Compression", "none");

endfunction

decompress("/home/luizz/Documents/materias/MAC0210/ep2/compressed.jpg", 1 , 1, 2)
