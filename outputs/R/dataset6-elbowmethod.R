r1 <- data.frame(
  k = 2:20,
  WCSS = c(2897.82, 2586.58, 939.22, 750.45, 445.12, 459.34, 235.97, 205.89,
           185.33, 215.78, 187.66, 184.29, 199.12, 182.54, 193.69, 172.58,
           175.21, 190.36, 179.48)
)


# Crear el conjunto de datos r2 con los nuevos valores de WCSS y las iteraciones
r2 <- data.frame(
  k = 2:20,
  WCSS = c(2800.74, 2800.74, 838.744, 153.738, 348.008, 356.711, 138.56, 108.214,
           89.2272, 112.755, 89.5144, 86.9075, 100.046, 80.2924, 95.1281, 75.8764,
           77.8579, 92.4828, 80.2935),
  Iteraciones = c(8, 2, 16, 7, 20, 66, 18, 21, 26, 48, 32, 59, 28, 85, 69, 61, 84, 44, 66)
)

# A partir de aquí, puedes proceder con la visualización o análisis adicional de estos datos según necesites
# A partir de aquí, puedes proceder con la visualización o anál

# Configurar el espacio de la trama para mostrar 2 gráficas lado a lado
par(mfrow = c(1, 2))

# Gráfica para el primer conjunto de datos
plot(r1$k, r1$WCSS, type = 'b', col = 'blue', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Medoids', pch = 19)

# Gráfica para el segundo conjunto de datos
plot(r2$k, r2$WCSS, type = 'b', col = 'red', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Means', pch = 19)

# Agregar un título de cabecera
mtext('Dataset 6: Comparación de WCSS por Número de Clusters', side = 3, line = 1, outer = TRUE, cex = 1.5)
