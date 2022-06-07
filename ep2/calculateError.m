function result = calculateError(originalImg,decompressedImg)
  ori = imread(originalImg);
  dec = imread(decompressedImg);
  oriR = ori(:,:,1);
  oriG = ori(:,:,2);
  oriB = ori(:,:,3);
  decR = dec(:,:,1);
  decG = dec(:,:,2);
  decB = dec(:,:,3);
  errR = norm(double(oriR) - double(decR), 2)/ norm(double(oriR), 2);
  errG = norm(double(oriG) - double(decG), 2)/ norm(double(oriG), 2);
  errB = norm(double(oriB) - double(decB), 2)/ norm(double(oriB), 2);
  erro = (errR + errG + errB) / 3;
  result = erro;
endfunction