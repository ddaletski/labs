least_squares = function (x, y) {
  a = 1.0
  b = 1.0
  learning_rate = 1e-3
  
  grad_a = 1
  grad_b = 1
  
  while (sqrt(abs(grad_a * grad_b)) > 1e-3) {
    y_hat = a * x + b
    
    grad_a = 2 * (y_hat - y) %*% x
    grad_b = sum(2 * (y_hat - y))
    
    a = a - learning_rate * grad_a
    b = b - learning_rate * grad_b
  }
  
  result = c(b, a)
  return(result)
}


unemployment = c(5.5, 5.3, 4.5, 3.8, 3.6, 4.0, 4.6)
inflation = c(1.8, 2.2, 3.7, 4.2, 4.3, 4.1, 3.7)

coeffs = least_squares(unemployment, inflation)
print(coeffs)

linmod = lm(inflation ~ unemployment)
print(linmod)

plot(x = unemployment, y = inflation)
abline(linmod, col='green')
abline(coeffs, col='red')

expected_unemployment = data.frame(unemployment=c(4.8))

expected_inflation_lm = predict.lm(linmod, expected_unemployment)
expected_inflation_manual = coeffs[1] + expected_unemployment$unemployment * coeffs[2]

print(paste("expected inflation according from lm:", expected_inflation_lm))
print(paste("expected inflation according computed:", expected_inflation_manual))
print(paste("difference in results:", abs(expected_inflation_lm - expected_inflation_manual)))

countries = read.table(file = 'allcountries.txt', sep = '', header = TRUE, strip.white = TRUE)
countries
attach(countries)

countries[is.na(area), 'area'] = median(area[!is.na(area)])
countries[is.na(population), 'population'] = median(population[!is.na(population)])
countries

with_na = is.na(gdp)
print(paste("nrows with NA:", sum(with_na)))

countries_model = lm(gdp ~ population + area + ind )
countries_model

countries[with_na, 'gdp'] = predict.lm(countries_model, countries[with_na, ])
countries[with_na, ]

countries
population_density = countries$population / countries$area
population_density

min_density_country = countries[which.min(population_density), ]
print(paste("country with minimal density (", max(population_density), ") :", min_density_country$country))
min_density_country