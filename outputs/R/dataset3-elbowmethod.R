r1 <- data.frame(
  k = 2:20,
  WCSS = c(387.343, 324.846, 256.441, 216.167, 192.78, 184.388, 168.499, 154.166,
           143.118, 136.809, 134.221, 122.831, 126.347, 114.341, 110.838, 113.484,
           103.63, 105.103, 98.0408)
)

# Actualizar el conjunto de datos r2 con los nuevos valores de WCSS y las iteraciones
r2 <- data.frame(
  k = 2:20,
  WCSS = c(381.627, 381.627, 315.413, 211.746, 250.8, 211.71, 153.414, 186.737,
           153.417, 153.532, 141.95, 167.275, 157.734, 126.405, 126.567, 147.052,
           126.951, 141.969, 101.674),
  Iteraciones = c(10, 11, 10, 26, 65, 45, 55, 49, 117, 25, 46, 63, 37, 96, 64, 32, 48, 81, 37)
)

# Configurar el espacio de la trama para mostrar 2 gráficas lado a lado
par(mfrow = c(1, 2))

# Gráfica para el primer conjunto de datos
plot(r1$k, r1$WCSS, type = 'b', col = 'blue', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Medoids', pch = 19)

# Gráfica para el segundo conjunto de datos
plot(r2$k, r2$WCSS, type = 'b', col = 'red', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Means', pch = 19)

# Agregar un título de cabecera
mtext('Dataset 3: Comparación de WCSS por Número de Clusters', side = 3, line = 1, outer = TRUE, cex = 1.5)
