#include <complex.h>
#include <math.h>
#include <png.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 100
#define REL_TOL 0.1
int maxIter = MAX_ITER;
double relTol = REL_TOL;

bool hasConverged(double complex x1, double complex x2, double tol) {
  return cabs(x2 - x1) < tol * cabs(x1);
}

double complex evalf(double complex x) { return x * x * x * x - 1; }
double complex evalDf(double complex x) { return 4 * x * x * x; }

double complex root1 = 1 + I;
double complex root2 = 1 - I;
double complex root3 = -1 + I;
double complex root4 = -1 - I;

int newton(double complex x0) {
  double complex x;

  for (int i = 0; i < maxIter; i++) {
    x = x0 - (evalf(x0) / evalDf(x0));
    x0 = x;
    if (hasConverged(x, x0, 0.5)) {
      if (hasConverged(x, root1, relTol)) {
        return 1;
      } else if (hasConverged(x, root2, relTol)) {
        return 2;
      } else if (hasConverged(x, root3, relTol)) {
        return 3;
      } else if (hasConverged(x, root4, relTol)) {
        return 4;
      }
    }
  }

  return 0;
}

void write_image(int h, int w, int *matrix, char *filename) {
  FILE *fp = NULL;
  fp = fopen(filename, "w");

  png_infop info_ptr = NULL;
  png_structp png_ptr =
      png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  png_init_io(png_ptr, fp);
  info_ptr = png_create_info_struct(png_ptr);

  // Write header (8 bit colour depth)
  png_set_IHDR(png_ptr, info_ptr, w, h, 8, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
               PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);

  png_bytep row = malloc(3 * w * sizeof(png_byte));

  // compose image
  int i, j;
  for (i = 0; i < h; i++) {
    for (j = 0; j < w; j++) {
      if (matrix[i * w + j] == 1) {
        row[3 * j] = 2;
        row[3 * j + 1] = 117;
        row[3 * j + 2] = 216;
      } else if (matrix[i * w + j] == 2) {
        row[3 * j] = 92;
        row[3 * j + 1] = 184;
        row[3 * j + 2] = 92;
      } else if (matrix[i * w + j] == 3) {
        row[3 * j] = 240;
        row[3 * j + 1] = 173;
        row[3 * j + 2] = 78;
      } else if (matrix[i * w + j] == 4) {
        row[3 * j] = 217;
        row[3 * j + 1] = 83;
        row[3 * j + 2] = 79;
      } else {
        row[3 * j] = 41;
        row[3 * j + 1] = 43;
        row[3 * j + 2] = 44;
      }
    }

    // write to the png file
    png_write_row(png_ptr, row);
  }
  png_write_end(png_ptr, NULL);

  free(row);
  png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
  png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
  fclose(fp);
}

void newton_basins(double complex l, double complex u, double complex p) {
  int stepsY = (cimag(u) - cimag(l)) / cimag(p);
  int stepsX = (creal(u) - creal(l)) / creal(p);

  int matrix[stepsY][stepsX];

  for (int i = 0; i < stepsY; i++) {
    for (int j = 0; j < stepsX; j++) {
      double complex currentCoord =
          (creal(l) + j * creal(p)) + (cimag(l) + i * cimag(p)) * I;
      int x = newton(currentCoord);
      matrix[i][j] = x;
      // printf("%d ", x);
    }
    // printf("\n");
  }

  write_image(stepsY, stepsX, (int *)matrix, "test1.png");
}

int main() { newton_basins(-2 - 2 * I, 2 + 2 * I, 0.01 + 0.01 * I); }