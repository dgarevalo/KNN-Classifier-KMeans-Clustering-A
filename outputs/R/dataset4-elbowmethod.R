r1 <- data.frame(
  k = 2:20,
  WCSS = c(207.71, 164.493, 153.686, 143.298, 139.163, 140.409, 134.39, 123.202,
           125.108, 118.841, 120.124, 112.661, 112.076, 116.121, 117.652, 112.029,
           112.284, 104.983, 98.9736)
)

# Actualizar el conjunto de datos r2 con los nuevos valores de WCSS y las iteraciones
r2 <- data.frame(
  k = 2:20,
  WCSS = c(235.629, 146.45, 147.032, 131.3, 121.331, 115.547, 122.028, 114.252,
           114.114, 117.508, 110.783, 96.4655, 106.757, 99.0223, 94.4177, 91.6876,
           95.0659, 94.2783, 98.9246),
  Iteraciones = c(2, 30, 22, 26, 25, 27, 25, 44, 41, 26, 48, 17, 38, 26, 24, 27, 18, 16, 19)
)

# Configurar el espacio de la trama para mostrar 2 gráficas lado a lado
par(mfrow = c(1, 2))

# Gráfica para el primer conjunto de datos
plot(r1$k, r1$WCSS, type = 'b', col = 'blue', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Medoids', pch = 19)

# Gráfica para el segundo conjunto de datos
plot(r2$k, r2$WCSS, type = 'b', col = 'red', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Means', pch = 19)

# Agregar un título de cabecera
mtext('Dataset 4: Comparación de WCSS por Número de Clusters', side = 3, line = 1, outer = TRUE, cex = 1.5)
