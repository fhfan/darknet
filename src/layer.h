#ifndef BASE_LAYER_H
#define BASE_LAYER_H

#include "activations.h"
#include "stddef.h"
#include "tree.h"

struct network;
typedef struct network network;

struct layer;
typedef struct layer layer;

typedef enum {
    CONVOLUTIONAL,
    DECONVOLUTIONAL,
    CONNECTED,
    MAXPOOL,
    SOFTMAX,
    DETECTION,
    DROPOUT,
    CROP,
    ROUTE,
    COST,
    NORMALIZATION,
    AVGPOOL,
    LOCAL,
    SHORTCUT,
    ACTIVE,
    RNN,
    GRU,
    CRNN,
    BATCHNORM,
    NETWORK,
    XNOR,
    REGION,
    REORG,
    BLANK               // 表示未识别的网络层名称
} LAYER_TYPE;

typedef enum{
    SSE, MASKED, L1, SMOOTH
} COST_TYPE;

// 下面注释部分是原来代码的参数排序，CPU与GPU之间的参数排序没有对应，比较乱，我重新排了一下，留此备份
/*
struct layer{
    LAYER_TYPE type;
    ACTIVATION activation;
    COST_TYPE cost_type;
    void (*forward)   (struct layer, struct network);
    void (*backward)  (struct layer, struct network);
    void (*update)    (struct layer, int, float, float, float);
    void (*forward_gpu)   (struct layer, struct network);
    void (*backward_gpu)  (struct layer, struct network);
    void (*update_gpu)    (struct layer, int, float, float, float);
    int batch_normalize;
    int shortcut;
    int batch;
    int forced;
    int flipped;
    int inputs;
    int outputs;
    int nweights;
    int nbiases;
    int extra;
    int truths;
    int h,w,c;
    int out_h, out_w, out_c;
    int n;
    int max_boxes;
    int groups;
    int size;
    int side;
    int stride;
    int reverse;
    int flatten;
    int pad;
    int sqrt;
    int flip;
    int index;
    int binary;
    int xnor;
    int steps;
    int hidden;
    int truth;
    float smooth;
    float dot;
    float angle;
    float jitter;
    float saturation;
    float exposure;
    float shift;
    float ratio;
    float learning_rate_scale;
    int softmax;
    int classes;
    int coords;
    int background;
    int rescore;
    int objectness;
    int does_cost;
    int joint;
    int noadjust;
    int reorg;
    int log;

    int adam;
    float B1;
    float B2;
    float eps;
    int t;

    float alpha;
    float beta;
    float kappa;

    float coord_scale;
    float object_scale;
    float noobject_scale;
    float class_scale;
    int bias_match;
    int random;
    float thresh;
    int classfix;
    int absolute;

    int onlyforward;
    int stopbackward;
    int dontload;
    int dontloadscales;

    float temperature;
    float probability;
    float scale;

    char  * cweights;
    int   * indexes;
    int   * input_layers;
    int   * input_sizes;
    int   * map;
    float * rand;
    float * cost;
    float * state;
    float * prev_state;
    float * forgot_state;
    float * forgot_delta;
    float * state_delta;

    float * concat;
    float * concat_delta;

    float * binary_weights;

    float * biases;
    float * bias_updates;

    float * scales;
    float * scale_updates;

    float * weights;
    float * weight_updates;

    float * delta;
    float * output;
    float * squared;
    float * norms;

    float * spatial_mean;
    float * mean;
    float * variance;

    float * mean_delta;
    float * variance_delta;

    float * rolling_mean;
    float * rolling_variance;

    float * x;
    float * x_norm;

    float * m;
    float * v;
    
    float * bias_m;
    float * bias_v;
    float * scale_m;
    float * scale_v;

    float * z_cpu;
    float * r_cpu;
    float * h_cpu;

    float * binary_input;

    struct layer *input_layer;
    struct layer *self_layer;
    struct layer *output_layer;

    struct layer *input_gate_layer;
    struct layer *state_gate_layer;
    struct layer *input_save_layer;
    struct layer *state_save_layer;
    struct layer *input_state_layer;
    struct layer *state_state_layer;

    struct layer *input_z_layer;
    struct layer *state_z_layer;

    struct layer *input_r_layer;
    struct layer *state_r_layer;

    struct layer *input_h_layer;
    struct layer *state_h_layer;

    tree *softmax_tree;

    size_t workspace_size;

    #ifdef GPU
    int *indexes_gpu;

    float *z_gpu;
    float *r_gpu;
    float *h_gpu;

    float *m_gpu;
    float *v_gpu;
    float *bias_m_gpu;
    float *scale_m_gpu;
    float *bias_v_gpu;
    float *scale_v_gpu;

    float * prev_state_gpu;
    float * forgot_state_gpu;
    float * forgot_delta_gpu;
    float * state_gpu;
    float * state_delta_gpu;
    float * gate_gpu;
    float * gate_delta_gpu;
    float * save_gpu;
    float * save_delta_gpu;
    float * concat_gpu;
    float * concat_delta_gpu;

    float *binary_input_gpu;
    float *binary_weights_gpu;

    float * mean_gpu;
    float * variance_gpu;

    float * rolling_mean_gpu;
    float * rolling_variance_gpu;

    float * variance_delta_gpu;
    float * mean_delta_gpu;

    float * x_gpu;
    float * x_norm_gpu;
    float * weights_gpu;
    float * weight_updates_gpu;

    float * biases_gpu;
    float * bias_updates_gpu;

    float * scales_gpu;
    float * scale_updates_gpu;

    float * output_gpu;
    float * delta_gpu;
    float * rand_gpu;
    float * squared_gpu;
    float * norms_gpu;
    #ifdef CUDNN
    cudnnTensorDescriptor_t srcTensorDesc, dstTensorDesc;
    cudnnTensorDescriptor_t dsrcTensorDesc, ddstTensorDesc;
    cudnnTensorDescriptor_t normTensorDesc;
    cudnnFilterDescriptor_t weightDesc;
    cudnnFilterDescriptor_t dweightDesc;
    cudnnConvolutionDescriptor_t convDesc;
    cudnnConvolutionFwdAlgo_t fw_algo;
    cudnnConvolutionBwdDataAlgo_t bd_algo;
    cudnnConvolutionBwdFilterAlgo_t bf_algo;
    #endif
    #endif
};
*/

struct layer{
    LAYER_TYPE type;            // 网络层的类型，枚举类型，取值比如DROPOUT,CONVOLUTIONAL,MAXPOOL分别表示dropout层，卷积层，最大池化层，可参见LAYER_TYPE枚举类型的定义
    ACTIVATION activation;
    COST_TYPE cost_type;
    void (*forward)   (struct layer, struct network);
    void (*backward)  (struct layer, struct network);
    void (*update)    (struct layer, int, float, float, float);
    void (*forward_gpu)   (struct layer, struct network);
    void (*backward_gpu)  (struct layer, struct network);
    void (*update_gpu)    (struct layer, int, float, float, float);
    int batch_normalize;        // 是否进行BN，如果进行BN，则值为1
    int shortcut;
    int batch;                  // 一个batch中含有的图片张数，等于net.batch，详细可以参考network.h中的注释，一般在构建具体网络层时赋值（比如make_maxpool_layer()中）
    int forced;
    int flipped;
    int inputs;                 // 一张输入图片所含的元素个数（一般在各网络层构建函数中赋值，比如make_connected_layer()），第一层的值等于l.h*l.w*l.c，
                                // 之后的每一层都是由上一层的输出自动推算得到的（参见parse_network_cfg()，在构建每一层后，会更新params.inputs为上一层的l.outputs）
                                
    int outputs;                // 该层对应一张输入图片的输出元素个数（一般在各网络层构建函数中赋值，比如make_connected_layer()）
                                // 对于一些网络，可由输入图片的尺寸及相关参数计算出，比如卷积层，可以通过输入尺寸以及跨度、核大小计算出；
                                // 对于另一些尺寸，则需要通过网络配置文件指定，如未指定，取默认值1，比如全连接层（见parse_connected()函数）
    int nweights;
    int nbiases;
    int extra;
    int truths;
    int h,w,c;                  // 该层输入图片的高、宽、通道数（一般在各网络层构建函数中赋值，比如make_connected_layer()），
                                // 第一层网络的h,w,c就是网络初始能够的接收的图片尺寸，而后每一层的h,w,c都与自动匹配上一层相应的输出参数，
                                // 不再需要配置文件指定（参见parse_network_cfg()，在构建每一层后，会更新params.h,params.w,params.c及params.inputs为上一层相应的输出参数），
                                // 对于全连接层，h,w直接置为1,c置为l.inputs（参见make_connected_layer()）

    int out_h, out_w, out_c;    // 该层输出图片的高、宽、通道数（一般在各网络层构建函数中赋值，比如make_connected_layer()），
                                // 对于卷积层，可由上面的h,w,c以及卷积核尺寸、跨度计算出；对于全连接层，out_h,out_w的值直接置为1,
                                // out_c直接置为l.outputs（参见make_connected_layer()）

    int n;                      // 卷积核个数，等于out_c
    int max_boxes;              // 每张图片最多处理的矩形框数（参看：data.c中的load_data_detection()）

    int groups;                 // 这个参数目前仅发现用在softmax_layer中，含义是将一张图片的数据分成几组，具体的值由网络配置文件指定，如未指定默认为1（见parse_softmax()），
                                // 很多网络都将该值设置为1，相当于没用到该值，我想这可能跟分类与分割粒度有关（如果粒度细些，估计会大于1,当然这只是个人猜测）

    int size;                   // 核尺寸（比如卷积核，池化核等）
    int side;
    int stride;
    int reverse;
    int flatten;
    int pad;                    // 该层对输入数据四周的补0长度（现在发现在卷积层，最大池化层中有用到该参数），一般在构建具体网络层时赋值（比如make_maxpool_layer()中）
    int sqrt;
    int flip;
    int index;
    int binary;
    int xnor;
    int steps;
    int hidden;
    int truth;
    float smooth;
    float dot;
    float angle;
    float jitter;
    float saturation;
    float exposure;
    float shift;
    float ratio;
    float learning_rate_scale;
    int softmax;
    int classes;
    int coords;
    int background;
    int rescore;
    int objectness;
    int does_cost;
    int joint;
    int noadjust;
    int reorg;
    int log;

    int adam;
    float B1;
    float B2;
    float eps;
    int t;

    float alpha;
    float beta;
    float kappa;

    float coord_scale;
    float object_scale;
    float noobject_scale;
    float class_scale;
    int bias_match;
    int random;
    float thresh;
    int classfix;
    int absolute;

    int onlyforward;
    int stopbackward;           // 暂时猜测该变量是标志参数，用来强制停止反向传播过程（值为1则停止反向传播），参看network.c中的backward_network()函数
    int dontload;
    int dontloadscales;

    float temperature;         // 温度参数，softmax层特有参数，在parse_softmax()函数中赋值，由网络配置文件指定，如果未指定，则使用默认值1（见parse_softmax()）
    float probability;         // dropout概率，即舍弃概率，相应的1-probability为保留概率（具体的使用可参见forward_dropout_layer()），在make_dropout_layer()中赋值，
                               // 其值由网络配置文件指定，如果网络配置文件未指定，则取默认值0.5（见parse_dropout()）
    float scale;               // 在dropout层中，该变量是一个比例因子，取值为保留概率的倒数（darknet实现用的是inverted dropout），用于缩放输入元素的值
                               // （在网上随便搜索关于dropout的博客，都会提到inverted dropout），在make_dropout_layer()函数中赋值

    char  * cweights;

    int   * input_layers;
    int   * input_sizes;
    int   * map;
    float * cost;

    float * spatial_mean;

    struct layer *input_layer;
    struct layer *self_layer;
    struct layer *output_layer;

    struct layer *input_gate_layer;
    struct layer *state_gate_layer;
    struct layer *input_save_layer;
    struct layer *state_save_layer;
    struct layer *input_state_layer;
    struct layer *state_state_layer;

    struct layer *input_z_layer;
    struct layer *state_z_layer;

    struct layer *input_r_layer;
    struct layer *state_r_layer;

    struct layer *input_h_layer;
    struct layer *state_h_layer;

    tree *softmax_tree;             // softmax层用到的一个参数，不过这个参数似乎并不常见，很多用到softmax层的网络并没用使用这个参数，目前仅发现darknet9000.cfg中使用了该参数，如果未用到该参数，其值为NULL，如果用到了则会在parse_softmax()中赋值，
                                    // 目前个人的初步猜测是利用该参数来组织标签数据，以方便访问

    size_t workspace_size;          // net.workspace的元素个数，为所有层中最大的l.out_h*l.out_w*l.size*l.size*l.c（在make_convolutional_layer()计算得到workspace_size的大小，在parse_network_cfg()中动态分配内存，此值对应未使用gpu时的情况）

    // CPU使用参数（GPU中按名字对应也有一套）
    int   * indexes;            // 维度为l.out_h * l.out_w * l.out_c * l.batch，可知包含整个batch输入图片的输出，一般在构建具体网络层时动态分配内存（比如make_maxpool_layer()中）。
                                // 目前仅发现其用在在最大池化层中。该变量存储的是索引值，并与当前层所有输出元素一一对应，表示当前层每个输出元素的值是上一层输出中的哪一个元素值（存储的索引值是
                                // 在上一层所有输出元素（包含整个batch）中的索引），因为对于最大池化层，每一个输出元素的值实际是上一层输出（也即当前层输入）某个池化区域中的最大元素值，indexes就是记录
                                // 这些局部最大元素值在上一层所有输出元素中的总索引。记录这些值有什么用吗？当然有，用于反向传播过程计算上一层敏感度值，详见backward_maxpool_layer()以及forward_maxpool_layer()函数。

    float * z_cpu;
    float * r_cpu;
    float * h_cpu;

    float * m;
    float * v;
    float * bias_m;
    float * scale_m;
    float * bias_v;
    float * scale_v;

    float * prev_state;
    float * forgot_state;
    float * forgot_delta;
    float * state;
    float * state_delta;

    float * concat;
    float * concat_delta;

    float * binary_input;
    float * binary_weights;

    float * mean;
    float * variance;

    float * rolling_mean;
    float * rolling_variance;

    float * variance_delta;
    float * mean_delta;

    float * x;
    float * x_norm;
    float * weights;            // 当前层所有权重系数（连接当前层和上一层的系数，但记在当前层上），对于卷积层，维度为l.n*l.c*l.size*l.size，即卷积核个数乘以卷积核尺寸再乘以输入通道数（各个通道上的权重系数不一样）；
                                // 对于全连接层，维度为单张图片输入与输出元素个数之积inputs*outputs，一般在各网络构建函数中动态分配内存（比如make_connected_layer()）
    float * weight_updates;     // 当前层所有权重系数更新值，对于卷积层维度为l.n*l.c*l.size*l.size；对于全连接层，维度为单张图片输入与输出元素个数之积inputs*outputs，
                                // 所谓权重系数更新值，就是梯度下降中与步长相乘的那项，也即误差对权重的导数，一般在各网络构建函数中动态分配内存（比如make_connected_layer()

    float * biases;             // 当前层所有偏置，对于卷积层，维度l.n，每个卷积核有一个偏置；对于全连接层，维度等于单张输入图片对应的元素个数即outputs，一般在各网络构建函数中动态分配内存（比如make_connected_layer()
    float * bias_updates;       // 当前层所有偏置更新值，对于卷积层，维度l.n，每个卷积核有一个偏置；对于全连接层，维度为outputs。所谓权重系数更新值，就是梯度下降中与步长相乘的那项，也即误差对偏置的导数，
                                // 一般在各网络构建函数中动态分配内存（比如make_connected_layer()

    float * scales;
    float * scale_updates;

    float * output;             // 存储该层所有的输出，维度为l.out_h * l.out_w * l.out_c * l.batch，可知包含整个batch输入图片的输出，一般在构建具体网络层时动态分配内存（比如make_maxpool_layer()中）。
                                // 按行存储：每张图片按行铺排成一大行，图片间再并成一行。

    float * delta;              // 存储每一层的敏感度图：包含所有输出元素的敏感度值（整个batch所有图片）。所谓敏感度，即误差函数关于当前层每个加权输入的导数值，
                                // 关于敏感度图这个名称，可以参考https://www.zybuluo.com/hanbingtao/note/485480。
                                // 元素个数为l.batch * l.outputs（其中l.outputs = l.out_h * l.out_w * l.out_c），
                                // 对于卷积神经网络，在make_convolutional_layer()动态分配内存，按行存储，可视为l.batch行，l.outputs列，
                                // 即batch中每一张图片，对应l.delta中的一行，而这一行，又可以视作有l.out_c行，l.out_h*l.out_c列，
                                // 其中每小行对应一张输入图片的一张输出特征图的敏感度。一般在构建具体网络层时动态分配内存（比如make_maxpool_layer()中）。

    float * rand;               // 这个参数目前只发现用在dropout层，用于存储一些列的随机数，这些随机数与dropout层的输入元素一一对应，维度为l.batch*l.inputs（包含整个batch的），在make_dropout_layer()函数中用calloc动态分配内存，
                                // 并在前向传播函数forward_dropout_layer()函数中逐元素赋值。里面存储的随机数满足0~1均匀分布，干什么用呢？用于决定该输入元素的去留，
                                // 我们知道dropout层就完成一个事：按照一定概率舍弃输入神经元（所谓舍弃就是置该输入的值为0），rand中存储的值就是如果小于l.probability，则舍弃该输入神经元（详见：forward_dropout_layer()）。
                                // 为什么要保留这些随机数呢？和最大池化层中的l.indexes类似，在反向传播函数backward_dropout_layer()中用来指示计算上一层的敏感度值，因为dropout舍弃了一些输入，
                                // 这些输入（dropout层的输入，上一层的输出）对应的敏感度值可以置为0，而那些没有舍弃的输入，才有必要由当前dropout层反向传播过去。
    float * squared;
    float * norms;

    // GPU使用参数（其中有四个在CPU中没有对应的参数）
    #ifdef GPU
    int *indexes_gpu;

    float *z_gpu;
    float *r_gpu;
    float *h_gpu;

    float *m_gpu;
    float *v_gpu;
    float *bias_m_gpu;
    float *scale_m_gpu;
    float *bias_v_gpu;
    float *scale_v_gpu;

    float * prev_state_gpu;
    float * forgot_state_gpu;
    float * forgot_delta_gpu;
    float * state_gpu;
    float * state_delta_gpu;
    // 以下四个参数在CPU中没有对应名称对应类型的参数
    float * gate_gpu;
    float * gate_delta_gpu;
    float * save_gpu;
    float * save_delta_gpu;
    // *******************************
    float * concat_gpu;
    float * concat_delta_gpu;

    float *binary_input_gpu;
    float *binary_weights_gpu;

    float * mean_gpu;
    float * variance_gpu;

    float * rolling_mean_gpu;
    float * rolling_variance_gpu;

    float * variance_delta_gpu;
    float * mean_delta_gpu;

    float * x_gpu;
    float * x_norm_gpu;
    float * weights_gpu;
    float * weight_updates_gpu;

    float * biases_gpu;
    float * bias_updates_gpu;

    float * scales_gpu;
    float * scale_updates_gpu;

    float * output_gpu;
    float * delta_gpu;
    float * rand_gpu;
    float * squared_gpu;
    float * norms_gpu;
    #ifdef CUDNN
    cudnnTensorDescriptor_t srcTensorDesc, dstTensorDesc;
    cudnnTensorDescriptor_t dsrcTensorDesc, ddstTensorDesc;
    cudnnTensorDescriptor_t normTensorDesc;
    cudnnFilterDescriptor_t weightDesc;
    cudnnFilterDescriptor_t dweightDesc;
    cudnnConvolutionDescriptor_t convDesc;
    cudnnConvolutionFwdAlgo_t fw_algo;
    cudnnConvolutionBwdDataAlgo_t bd_algo;
    cudnnConvolutionBwdFilterAlgo_t bf_algo;
    #endif
    #endif
};



void free_layer(layer);

#endif
