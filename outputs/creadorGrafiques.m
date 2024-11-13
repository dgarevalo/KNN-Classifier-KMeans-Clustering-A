% Define la carpeta principal
carpeta_principal = '/Experiments'; % Cambia esto a tu carpeta principal

% Obtiene una lista de todas las subcarpetas
todas_subcarpetas = genpath(carpeta_principal);
% Divide la lista en un array de nombres de carpetas
carpetas = split(todas_subcarpetas, ';');
centroides_kmeans = [];
centroides_kmeanspp = [];
centroides_kmedoids = [];
datos_kmeans = [];
datos_kmeanspp = [];
datos_kmedoids = [];
siluetas_kmeans = [];
siluetas_kmeanspp = [];
siluetas_kmedoids = [];


% Recorre cada carpeta
for i = 3:length(carpetas)
    centroides_kmeans = [];
    centroides_kmeanspp = [];
    centroides_kmedoids = [];
    datos_kmeans = [];
    datos_kmeanspp = [];
    datos_kmedoids = [];
    siluetas_kmeans = [];
    siluetas_kmeanspp = [];
    siluetas_kmedoids = [];
    entra = false;
    carpeta_actual = carpetas{i};
    % Obtiene una lista de todos los archivos .txt en la carpeta actual
    archivos = dir(fullfile(carpeta_actual, '*.txt'));
    % Recorre cada archivo .txt
    for j = 1:length(archivos)
        entra = true;
        archivo_actual = fullfile(archivos(j).folder, archivos(j).name);
        % Abre el archivo para lectura
        fid = fopen(archivo_actual, 'r');

        % Variables para almacenar los datos
        
        % Variables auxiliares para controlar qué sección estamos leyendo
        seccion_actual = '';
        leyendo_centroides = false;
        leyendo_datos = false;
        leyendo_siluetas = false;
        leyendo_tiempo_ejecucion = false;
        
        % Lee línea por línea del archivo
        tline = fgetl(fid);
        while ischar(tline)
            % Verifica en qué sección estamos
            if startsWith(tline, 'Dades Kmeans++')
                seccion_actual = 1;
                leyendo_centroides = false;
                leyendo_datos = true;
                leyendo_siluetas = false;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Centroides Kmeans++')
                seccion_actual = 1;
                leyendo_centroides = true;
                leyendo_datos = false;
                leyendo_siluetas = false;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Siluetes Kmeans++')
                seccion_actual = 1;
                leyendo_centroides = false;
                leyendo_datos = false;
                leyendo_siluetas = true;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Siluetes Kmeans')
                seccion_actual = 0;
                leyendo_centroides = false;
                leyendo_datos = false;
                leyendo_siluetas = true;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Centroides Kmeans')
                seccion_actual = 0;
                leyendo_centroides = true;
                leyendo_datos = false;
                leyendo_siluetas = false;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Dades Kmeans')
                seccion_actual = 0;
                leyendo_centroides = false;
                leyendo_datos = true;
                leyendo_siluetas = false;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Siluetes KMedoids')
                seccion_actual = 2;
                leyendo_centroides = false;
                leyendo_datos = false;
                leyendo_siluetas = true;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Centroides KMedoids')
                seccion_actual = 2;
                leyendo_centroides = true;
                leyendo_datos = false;
                leyendo_siluetas = false;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, 'Dades KMedoids')
                seccion_actual = 2;
                leyendo_centroides = false;
                leyendo_datos = true;
                leyendo_siluetas = false;
                leyendo_tiempo_ejecucion = false;
            elseif startsWith(tline, '*****')
                leyendo_centroides = false;
                leyendo_datos = false;
                leyendo_siluetas = false;
                leyendo_tiempo_ejecucion = true;
            else
                % Lee los datos según la sección actual
                if leyendo_centroides
                    % Lee los centroides y los almacena en la matriz correspondiente
                    centroides = str2double(strsplit(tline));
                    switch seccion_actual
                        case 0
                            centroides_kmeans = [centroides_kmeans; centroides];
                        case 1
                            centroides_kmeanspp = [centroides_kmeanspp; centroides];
                        case 2
                            centroides_kmedoids = [centroides_kmedoids; centroides];
                    end
                elseif leyendo_datos
                    % Lee los datos y los almacena en la matriz correspondiente
                    datos = str2double(strsplit(tline));
                    switch seccion_actual
                        case 0
                            datos_kmeans = [datos_kmeans; datos];
                        case 1
                            datos_kmeanspp = [datos_kmeanspp; datos];
                        case 2
                            datos_kmedoids = [datos_kmedoids; datos];
                    end
                elseif leyendo_siluetas
                    % Lee las siluetas y las almacena en la matriz correspondiente
                    silueta = str2double(strsplit(tline));
                    switch seccion_actual
                        case 0
                            siluetas_kmeans = [siluetas_kmeans; silueta];
                        case 1
                            siluetas_kmeanspp = [siluetas_kmeanspp; silueta];
                        case 2
                            siluetas_kmedoids = [siluetas_kmedoids; silueta];
                    end
                end
            end
            tline = fgetl(fid);
        end
        %% 
        fclose(fid);
    end

    if entra
        filename1 = sprintf('%d_clusters_kmeans.png', i-1);
        filename2 = sprintf('%d_clusters_kmeanspp.png', i-1);
        filename3 = sprintf('%d_clusters_kmedoids.png', i-1);
        filename4 = sprintf('%d_siluetes_kmeans.png', i-1);
        filename5 = sprintf('%d_siluetes_kmeanspp.png', i-1);
        filename6 = sprintf('%d_siluetes_kmedoids.png', i-1);
        % Graficar puntos y centroides para kmeans
        figure;
        %gscatter(datos_kmeans(:,1), datos_kmeans(:,2), datos_kmeans(:,end));
        h0 = gscatter(datos_kmeans(:,1), datos_kmeans(:,2), datos_kmeans(:,end));
        hold on;
        for grup = 1:2
            text(centroides_kmeans(grup,1), centroides_kmeans(grup,2), num2str(grup-1), "HorizontalAlignment", 'center', 'VerticalAlignment','middle');
        end
        %h = gscatter(centroides_kmeans(:,1), centroides_kmeans(:,2), centroides_kmeans(:,end));
        %set(h, 'Marker', 'x', 'MarkerSize', 10, 'LineWidth', 3);
        %gscatter(centroides_kmeans(:,1), centroides_kmeans(:,2), [], centroides_kmeans(:,end), 'x', 'LineWidth', 3);
        %plot(centroides_kmeans(:,1), centroides_kmeans(:,2), 'kx', 'MarkerSize', 15, 'LineWidth', 3);
        title('Clusters para kmeans');
        xlabel('Dimensión 1');
        ylabel('Dimensión 2');
        hold off;
        saveas(gcf, filename1);
        
        % Graficar puntos y centroides para kmeans++
        figure;
        gscatter(datos_kmeanspp(:,1), datos_kmeanspp(:,2),datos_kmeanspp(:,end));
        hold on;
        
        for grup = 1:2
            text(centroides_kmeanspp(grup,1), centroides_kmeanspp(grup,2), num2str(grup-1), "HorizontalAlignment", 'center', 'VerticalAlignment','middle');
        end
        %h2 = gscatter(centroides_kmeanspp(:,1), centroides_kmeanspp(:,2), centroides_kmeanspp(:,end));
        %set(h2, 'Marker', 'x', 'MarkerSize', 10, 'LineWidth', 3);
        %plot(centroides_kmeanspp(:,1), centroides_kmeanspp(:,2), 'kx', 'MarkerSize', 15, 'LineWidth', 3);
        %scatter(centroides_kmeanspp(:,1), centroides_kmeanspp(:,2), 100, 'rx', 'LineWidth', 2);
        title('Clusters para kmeans++');
        xlabel('Dimensión 1');
        ylabel('Dimensión 2');
        hold off;
        saveas(gcf, filename2);
        
        % Graficar puntos y centroides para kmeans++
        figure;
        gscatter(datos_kmedoids(:,1), datos_kmedoids(:,2),datos_kmedoids(:,end));
        hold on;

        for grup = 1:2
            text(datos_kmedoids(grup,1), datos_kmedoids(grup,2), num2str(grup-1), "HorizontalAlignment", 'center', 'VerticalAlignment','middle');
        end
        %h2 = gscatter(centroides_kmeanspp(:,1), centroides_kmeanspp(:,2), centroides_kmeanspp(:,end));
        %set(h2, 'Marker', 'x', 'MarkerSize', 10, 'LineWidth', 3);
        %plot(centroides_kmeanspp(:,1), centroides_kmeanspp(:,2), 'kx', 'MarkerSize', 15, 'LineWidth', 3);
        %scatter(centroides_kmeanspp(:,1), centroides_kmeanspp(:,2), 100, 'rx', 'LineWidth', 2);
        title('Clusters para kmedoids');
        xlabel('Dimensión 1');
        ylabel('Dimensión 2');
        hold off;
        saveas(gcf, filename3);
        
        % Graficar siluetas para kmeans
        figure;
        histogram(siluetas_kmeans(:), linspace(-1, 1, 20), 'Normalization', 'probability');
        title('Siluetas para kmeans');
        xlabel('Valor de silueta');
        ylabel('Frecuencia relativa');
        saveas(gcf, filename4);
        
        % Graficar siluetas para kmeans++
        figure;
        histogram(siluetas_kmeanspp(:), linspace(-1, 1, 20), 'Normalization', 'probability');
        title('Siluetas para kmeans++');
        xlabel('Valor de silueta');
        ylabel('Frecuencia relativa');
        saveas(gcf, filename5);
        
        % Graficar siluetas para kmeans++
        figure;
        histogram(siluetas_kmedoids(:), linspace(-1, ...
            1, 20), 'Normalization', 'probability');
        title('Siluetas para kmedoids');
        xlabel('Valor de silueta');
        ylabel('Frecuencia relativa');
        saveas(gcf, filename6);
    end
end
   
%% 
