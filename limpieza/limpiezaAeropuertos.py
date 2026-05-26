## import polars as pl

df_airports = pl.read_csv(
    "airports.dat",
    separator=",",
    null_values="\\N",
    quote_char='"',
    has_header=False,
    new_columns=[
        "id",
        "nombre",
        "ciudad",
        "pais",
        "IATA",
        "ICAO",
        "Latitud",
        "Longitud",
        "Altitud",
        "Zona Horaria",
        "DST",
        "tz_database",
        "Tipo",
        "Fuente"
    ]
)

df_airports_final = df_airports.select([
    "id",
    "nombre",
    "ciudad",
    "pais",
    "IATA",
    "ICAO",
    "Latitud",
    "Longitud"
]).filter(
    pl.col("IATA").is_not_null()
)

## display(df_airports_final.head())