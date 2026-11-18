import csv
import math

# Step 1: Read dataset
data = []

with open("food_data.csv", "r") as file:
    reader = csv.DictReader(file)

    for row in reader:
        row = {key.strip().lower(): value for key, value in row.items()}

        prepared = float(row["prepared"])
        waste = float(row["waste"])

        data.append((prepared, waste))

# Step 2: Separate input and output
X = [item[0] for item in data]
Y = [item[1] for item in data]

# Step 3: Train Linear Regression Model
n = len(X)

if n < 2:
    print("At least 2 records are required.")
    exit()

mean_x = sum(X) / n
mean_y = sum(Y) / n

numerator = sum(
    (X[i] - mean_x) * (Y[i] - mean_y)
    for i in range(n)
)

denominator = sum(
    (X[i] - mean_x) ** 2
    for i in range(n)
)

if denominator == 0:
    print("Cannot train model: prepared values are identical.")
    exit()

slope = numerator / denominator
intercept = mean_y - slope * mean_x

# Step 4: Make predictions on existing data
predictions = [
    slope * X[i] + intercept for i in range(n)
]

# Step 5: Calculate model error
mae = sum(
    abs(Y[i] - predictions[i]) for i in range(n)
) / n

rmse = math.sqrt(
    sum(
        (Y[i] - predictions[i]) ** 2 for i in range(n)
    ) / n
)

# Step 6: Display model results
print("FOOD WASTE ML MODEL")
print("-------------------")
print("Algorithm: Linear Regression")
print("Training Records:", n)
print("MAE:", round(mae, 2))
print("RMSE:", round(rmse, 2))

# Step 7: Predict future food waste
prepared_quantity = float(
    input("\nEnter next day's prepared food quantity: ")
)

predicted_waste = slope * prepared_quantity + intercept
predicted_waste = max(0, predicted_waste)

print("Predicted Food Waste:", round(predicted_waste, 2))

# Step 8: Save test results
with open("test_results.csv", "w", newline="") as file:
    writer = csv.writer(file)

    writer.writerow([
        "Actual Waste",
        "Predicted Waste",
        "Absolute Error"
    ])

    for i in range(n):
        writer.writerow([
            Y[i],
            round(predictions[i], 2),
            round(abs(Y[i] - predictions[i]), 2)
        ])

# Step 9: Save trained model coefficients
with open("trained_model.txt", "w") as file:
    file.write("Algorithm: Linear Regression\n")
    file.write("Slope: " + str(slope) + "\n")
    file.write("Intercept: " + str(intercept) + "\n")

print("\nTest results saved successfully!")
print("Trained model details saved successfully!")