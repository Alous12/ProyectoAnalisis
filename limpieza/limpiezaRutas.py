df_routes = pl.read_csv(
    "routes.dat",
    separator=",",
    null_values="\\N",
    quote_char='"',
    has_header=False,
    new_columns=[
        "Aereolinea",
        "ID_Aereolinea",
        "Origen",
        "ID_Origen",
        "Destino",
        "ID_Destino",
        "Codeshare",
        "Paradas",
        "Equipo"
    ]
)

airport_ids = df_airports_final["id"].to_list()

df_routes_final = (
    df_routes
    .select(["ID_Destino", "ID_Origen", "Aereolinea", "ID_Aereolinea"])
    .filter(
        pl.col("ID_Origen").is_not_null() &
        pl.col("ID_Destino").is_not_null() &
        pl.col("ID_Aereolinea").is_not_null() &
        pl.col("ID_Origen").is_not_null() &
        (pl.col("ID_Origen") != pl.col("ID_Destino")) &
        pl.col("ID_Origen").is_in(airport_ids) &
        pl.col("ID_Destino").is_in(airport_ids)
    )
    .unique(subset=["ID_Origen", "ID_Destino"])
)


display(df_routes_final.head())
