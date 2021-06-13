from branca import colormap
import folium

f = open("test2.txt", "r")
reading= f.read().split(',')

#Map object
map_object = folium.Map(location=[reading[0], reading[1]], zoom_start=15)

#Markers for start and end locations
folium.Marker(location=[reading[0], reading[1]], icon=folium.Icon(color='red')).add_to(map_object),
folium.Marker(location=[reading[-2], reading[-1]], icon=folium.Icon(color='red')).add_to(map_object)

#plotting points
for i in range(0, len(reading)-1, 2):
    folium.CircleMarker([reading[i], reading[i+1]],
                        fill = True,
                        color = 'blue',
                        radius = 10,
                        fill_color = 'blue').add_to(map_object)

map_object.save('map.html')
