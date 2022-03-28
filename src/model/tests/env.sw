# ENV.sw

(A env/Getenv)->(P sw/Print);
(D)->(B sw/linux/Wrap "echo DEBUG=Y")1->(C env/Setenv);
