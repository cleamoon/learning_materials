import folium, pandas, math
map = folium.Map(location = [38.58, -99.09], zoom_start = 5)
data = pandas.read_csv("Volcanoes.csv")
lat = list(data["LAT"])
lon = list(data["LON"])
elev = list(data["ELEV"])

def elevation_to_color(el): 
    if el < 1000:
        return "green"
    elif 1000 <= el < 3000:
        return "orange"
    else:
        return "red"

fg = folium.FeatureGroup(name = "My map")

for lt, ln, el in zip(lat, lon, elev):
    fg.add_child(folium.CircleMarker(location = [lt, ln], popup = folium.Popup("Elevation: " + str(el) + " m", parse_html = True), fill_color = elevation_to_color(el), color = "grey", fill_opacity = 0.6, radius = el/200))

fg.add_child(folium.LayerControl())

map.add_child(fg)
map.save("map.html")