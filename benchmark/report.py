import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from pdb import set_trace as bp
sns.set(style='whitegrid')
sns.set_palette(sns.color_palette("muted"))
sns.despine()

def plot_stuff(name, df, log=False):
    plt.clf()
    xaxis = df.index
    fig, ax = plt.subplots()
    ax.plot(xaxis, df['bst_insert'], 'o', alpha=0.8, label='bst_insert')
    ax.plot(xaxis, df['avl_insert'], 'o', alpha=0.8, label='avl_insert')
    ax.plot(xaxis, df['rb_insert'], 'o', alpha=0.8, label='rb_insert')
    if log:
        plt.yscale('log')
        name += ' (log)'
    fig.suptitle(name, fontsize=22)
    ax.legend(loc='best', fontsize='large', frameon=True)
    plt.savefig('img/'+name+'_insert.png', bbox_inches='tight', dpi=300)
    plt.clf()


    fig, ax = plt.subplots()
    fig.suptitle(name, fontsize=22)
    ax.plot(xaxis, df['bst_search'], 'o', alpha=0.8, label='bst_search')
    ax.plot(xaxis, df['avl_search'], 'o', alpha=0.8, label='avl_search')
    ax.plot(xaxis, df['rb_search'], 'o', alpha=0.8, label='rb_search')
    if log: plt.yscale('log')
    ax.legend(loc='best', fontsize='large', frameon=True)
    plt.savefig('img/'+name+'_search.png', bbox_inches='tight', dpi=300)
    plt.clf()

    fig, ax = plt.subplots()
    fig.suptitle(name, fontsize=22)
    ax.plot(xaxis, df['bst_height'], 'o', alpha=0.8, label='bst_height')
    ax.plot(xaxis, df['avl_height'], 'o', alpha=0.8, label='avl_height')
    ax.plot(xaxis, df['rb_height'], 'o', alpha=0.8, label='rb_height')
    if log: plt.yscale('log')
    fig.suptitle(name, fontsize=22)
    ax.legend(loc='best', fontsize='large', frameon=True)
    plt.savefig('img/'+name+'_height.png', bbox_inches='tight', dpi=300)
    plt.clf()


df = pd.DataFrame.from_csv("tree_performance.csv",sep=',')
plot_stuff('Average case', df)

df = pd.DataFrame.from_csv("tree_performance_worst.csv",sep=',')
plot_stuff('Worst case', df)
plot_stuff('Worst case', df, True)
