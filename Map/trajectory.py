from branca import colormap
import folium

#Map object
map_object = folium.Map(location=[30.27907395362854, 31.064562795948223], zoom_start=15)

#Markers for start and end locations
folium.Marker(location=[42.363600,-71.099500], icon=folium.Icon(color='red')).add_to(map_object),
folium.Marker(location=[42.333600,-71.109500], icon=folium.Icon(color='red')).add_to(map_object)

#Moving circle marker   
folium.CircleMarker(location=[30.27907395362854, 31.064562795948223], 
                    radius=5,
                    color='#428bca',
                    fill=True,
                    fill_color='#428bca').add_to(map_object)

map_object.save('map.html')
