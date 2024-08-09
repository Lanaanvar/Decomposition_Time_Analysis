# Decomposition_Time_Analysis

This project demonstrates how to perform QR, LU, and Cholesky decompositions on symmetric positive definite (SPD) matrices using the Eigen library in C++. It measures the average time taken for each decomposition method and provides a comparison of their performance.

## Table of Contents

- [Introduction](#introduction)
- [Decomposition Details](#decomposition-details)
- [Performance Measurement](#performance-measurement)


## Introduction
This project defines a `MatrixDecomposer` class that performs matrix decompositions on randomly generated symmetric positive definite (SPD) matrices. It showcases three decomposition techniques:

- **QR Decomposition**
- **LU Decomposition**
- **Cholesky Decomposition**

## Decomposition Details

- QR Decomposition: Factorizes a matrix into a product of an orthogonal matrix (Q) and an upper triangular matrix (R).
- LU Decomposition: Decomposes a matrix into a product of a lower triangular matrix (L) and an upper triangular matrix (U).
- Cholesky Decomposition: Performs a specialized LU decomposition for symmetric positive definite matrices, resulting in a lower triangular matrix (L).

## Performance Measurement
The program measures the average time taken for each decomposition method over a fixed number of iterations (10 by default). The performance results are displayed as:

- Average QR Decomposition Time
- Average LU Decomposition Time
- Average Cholesky Decomposition Time
- The ratios of the times taken by QR, LU, and Cholesky decompositions are also displayed for comparison.
