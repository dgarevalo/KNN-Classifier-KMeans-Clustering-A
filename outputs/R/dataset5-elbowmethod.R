# Actualizar el conjunto de datos r1 con los nuevos valores de WCSS
r1 <- data.frame(
  k = 2:20,
  WCSS = c(10614.3, 9808.03, 8876.44, 8686.81, 8228.14, 8159.58, 7504.61, 7707.53,
           7255.11, 7026.67, 7349.99, 6494.6, 6781.75, 6134.97, 6376.17, 6033.97,
           6123.58, 6021.99, 5958.97)
)

# Actualizar el conjunto de datos r2 con los nuevos valores de WCSS y las iteraciones
r2 <- data.frame(
  k = 2:20,
  WCSS = c(9084.68, 8084.44, 7301.69, 6874.24, 6617.8, 6302.46, 6357.29, 5881.51,
           5711.7, 5584.76, 5490.53, 5581.59, 5269.35, 5131.88, 5250.28, 4977.4,
           4803.35, 4817.79, 4938.47),
  Iteraciones = c(16, 11, 20, 27, 28, 39, 41, 27, 30, 48, 20, 31, 30, 40, 21, 24, 32, 27, 27)
)

# A partir de aquí, puedes proceder con la visualización o anál

# Configurar el espacio de la trama para mostrar 2 gráficas lado a lado
par(mfrow = c(1, 2))

# Gráfica para el primer conjunto de datos
plot(r1$k, r1$WCSS, type = 'b', col = 'blue', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Medoids', pch = 19)

# Gráfica para el segundo conjunto de datos
plot(r2$k, r2$WCSS, type = 'b', col = 'red', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Means', pch = 19)

# Agregar un título de cabecera
mtext('Dataset 5: Comparación de WCSS por Número de Clusters', side = 3, line = 1, outer = TRUE, cex = 1.5)

