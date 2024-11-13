# Primer conjunto de datos
datos1 <- data.frame(
  k = 2:20,
  WCSS = c(563.097, 467.264, 363.351, 320.695, 319.598, 297.395, 284.85, 237.182,
           268.495, 266.652, 227.673, 229.715, 186.056, 187.02, 159.702, 147.77,
           139.826, 161.886, 147.653)
)

# Segundo conjunto de datos
datos2 <- data.frame(
  k = 2:20,
  WCSS = c(332.185, 293.275, 254.647, 243.181, 227.453, 215.644, 189.867, 201.526,
           166.557, 148.383, 159.738, 119.855, 148.822, 152.155, 156.844, 141.917,
           117.513, 143.18, 113.681)
)

# Agregar un título de cabecera
mtext('Comparación de WCSS por Número de Clusters', side = 3, line = -2, outer = TRUE, cex = 1.5)
# Crear las gráficas
par(mfrow=c(1,2)) # Configura el layout para mostrar 2 gráficas una al lado de la otra

# Gráfica para el primer conjunto de datos
plot(datos1$k, datos1$WCSS, type='b', col='blue', xlab='Número de Clusters (k)', ylab='WCSS', main='K-Medoids')

# Gráfica para el segundo conjunto de datos
plot(datos2$k, datos2$WCSS, type='b', col='red', xlab='Número de Clusters (k)', ylab='WCSS', main='K-Means')


par(mfrow = c(1, 2), oma = c(4, 4, 4, 2), mar = c(4, 4, 2, 1))

# Gráfica para el primer conjunto de datos
plot(datos1$k, datos1$WCSS, type = 'b', col = 'blue', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Medoids')

# Gráfica para el segundo conjunto de datos
plot(datos2$k, datos2$WCSS, type = 'b', col = 'red', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Means')

# Agregar un título de cabecera
mtext('Dataset 2: Comparación de WCSS por Número de Clusters', side = 3, line = 1, outer = TRUE, cex = 1.5)

