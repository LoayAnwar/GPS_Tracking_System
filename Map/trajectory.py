from branca import colormap
import folium

latitude = [30.288633346557617, 30.290264129638672, 31.273269653320316, 31.25301361083984]
longitude = [30.076298837912606, 30.084394409909613, 30.086028298208685, 30.08231487667201]

#Map object
map_object = folium.Map(location=[latitude[0], longitude[0]], zoom_start=15)

#Markers for start and end locations
folium.Marker(location=[latitude[0], longitude[0]], icon=folium.Icon(color='red')).add_to(map_object),
folium.Marker(location=[latitude[-1], longitude[-1]], icon=folium.Icon(color='red')).add_to(map_object)

for i in range(len(latitude)):
    folium.CircleMarker([latitude[i], longitude[i]],
                        fill = True,
                        color = 'blue',
                        radius = 10,
                        fill_color = 'blue').add_to(map_object)

map_object.save('map.html')
