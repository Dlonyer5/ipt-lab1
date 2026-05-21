from django.urls import path
from .views import product_service

urlpatterns = [
    path('', product_service),
]