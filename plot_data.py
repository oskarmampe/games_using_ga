import os
import pandas as pd
import matplotlib.pyplot as plt

'''
  This script should be put wherever the folders with the results lie.
  It will iterate through all the folders with the results and create a condensed version of the csvs.
'''

# Get directories
d = '.'
direc = [os.path.join(d, o) for o in os.listdir(d) if os.path.isdir(os.path.join(d,o))]

for dire in direc: # For each directory
  print(dire+'\\data.csv')
  # Create a dataframe from the csv
  df = pd.read_csv(dire+'\\data.csv', header=None, skiprows=[0],names=["Fitness", "Strategy", "t"])
  # Create a new dataframe which is grouped, and add mean/count/max/min/std of fitness value
  xc = df.groupby(['t', 'Strategy']).agg(['mean', 'count', 'max', 'min', 'std']).reset_index()
  # Create another dataframe to allow to group by count and create percentages
  test = df.groupby(['t', 'Strategy']).agg({'Fitness':'count'})
  # Create the last dataframe which is a dataframe with percentages
  percentage = test.groupby(level=0).apply(lambda x: 100 * x / float(x.sum())).reset_index()

  # Fix the columns. After grouping, the headers are in two different rows. This fixes it
  xc.columns = ["_".join(x) for x in xc.columns.ravel()]
  # Rename the columns to be more appropriate
  xc.rename(columns={'t_': 'Generation', 'Strategy_': 'Strategy', 'Fitness_mean':'Average Fitness','Fitness_count':'Population Count','Fitness_max':'Maximum Fitness','Fitness_min':'Minimum Fitness','Fitness_std':'Standard Deviation of Fitness'}, inplace=True)
  # Join the percentage and grouped dataframes
  xc['Total in Lattice %'] = percentage['Fitness']

  # Get rows by strategy
  x = xc.loc[xc['Strategy'] == 'c']
  x2 = xc.loc[xc['Strategy'] == 'd']
  
  # Create the plots of population count over t
  plt.plot(x['Generation'], x['Population Count'], label='Cooperators', color='blue')
  plt.plot(x2['Generation'], x2['Population Count'], label='Defectors', color='red')
  plt.savefig(dire+'\\count.png')

  # Clear the plot
  plt.clf()

  # Create the Average fitness over t plots
  plt.plot(x['Generation'], x['Average Fitness'], label='Cooperators', color='blue')
  plt.plot(x2['Generation'], x2['Average Fitness'], label='Defectors', color='red')
  plt.savefig(dire+'\\Fitness_mean.png') 

  # Rearrange the columns in a more appealing/readable way
  xc = xc[['Generation', 'Strategy', 'Average Fitness', 'Standard Deviation of Fitness', 'Maximum Fitness', 'Minimum Fitness', 'Population Count', 'Total in Lattice %']]
  
  # Save the dataframe to a csv, but make sure to only get 4 total t values
  xc.loc[(xc['Generation'] % (xc['Generation'].max() / 2) == 0) | (xc['Generation'] == 1)].to_csv (dire+'\\small.csv', index=False, header=True, float_format='%.3f')
