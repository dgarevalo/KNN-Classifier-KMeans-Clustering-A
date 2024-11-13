# Crear los conjuntos de datos
r1 <- data.frame(
  k = 2:20,
  WCSS = c(2630.84, 2123.48, 1939.06, 1390.41, 1416.12, 1333.28, 1202.17, 754.569,
           754.055, 768.089, 646.311, 708.82, 608.875, 659.247, 582.438, 631.371,
           567.598, 553.379, 527.556)
)

r2 <- data.frame(
  k = 2:20,
  WCSS = c(2554.23, 2070.83, 1424.55, 1424.55, 1084.73, 939.654, 1059.42, 1084.73,
           1064.88, 774.687, 830.281, 726.468, 830.359, 826.635, 975.552, 594.809,
           744.775, 668.307, 824.254)
)

# Configurar el espacio de la trama para mostrar 2 gráficas lado a lado
par(mfrow = c(1, 2))

# Gráfica para el primer conjunto de datos
plot(r1$k, r1$WCSS, type = 'b', col = 'blue', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Medoids', pch = 19)

# Gráfica para el segundo conjunto de datos
plot(r2$k, r2$WCSS, type = 'b', col = 'red', xlab = 'Número de Clusters (k)', ylab = 'WCSS', main = 'K-Means', pch = 19)

# Agregar un título de cabecera
mtext('Dataset 1: Comparación de WCSS por Número de Clusters', side = 3, line = 1, outer = TRUE, cex = 1.5)
